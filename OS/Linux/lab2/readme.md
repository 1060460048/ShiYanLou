# lab2 系统内存的探测
[博客](https://segmentfault.com/a/1190000009450840)

    主要涉及操作系统的物理内存管理。
    操作系统为了使用内存，还需高效地管理内存资源。
    这里我们会了解并且自己动手完成一个简单的物理内存管理系统。

# 实验目的
    理解基于段页式内存地址的转换机制
    理解页表的建立和使用方法
    理解物理内存的管理方法

# 实验内容 
    1. 首先了解如何发现系统中的物理内存；
    2. 然后了解如何建立对物理内存的初步管理，即了解连续物理内存管理；
    3. 最后了解页表相关的操作，即如何建立页表来实现虚拟内存到物理内存之间的映射，对段页式内存管理机制有一个比较全面的了解。
    本实验里面实现的内存管理还是非常基本的，并没有涉及到对实际机器的优化，比如针对 cache(缓冲区)的优化等。
    如果大家有余力，尝试完成扩展练习。
![](https://img-blog.csdn.net/20170903193711721?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvZm91eV95dW4=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)
    
# 练习1：实现 first-fit 连续物理内存分配算法（需要编程）
    在实现first fit 内存分配算法的回收函数时，要考虑地址连续的空闲块之间的合并操作。
    提示:在建立空闲页块链表时，需要按照空闲页块起始地址来排序，形成一个有序的链表。
    可能会修改default_pmm.c中的default_init，default_init_memmap，default_alloc_pages， default_free_pages等相关函数。
    请仔细查看和理解default_pmm.c中的注释。
## 软件了解硬件实际物理内存(物理内存如何分布的，哪些可用，哪些不可用)
    探测物理内存分布和大小的方法, 基本方法是通过BIOS中断调用来帮助完成的。
    其中BIOS中断调用必须在实模式下进行，所以在bootloader进入保护模式前完成这部分工作相对比较合适。
    所以需要修改bootloader软件。这些部分由boot/bootasm.S中从probe_memory处到finish_probe处的代码部分完成。
    通过BIOS中断获取内存可调用参数为e820h的INT 15h BIOS中断。
    BIOS通过系统内存映射地址描述符（Address Range Descriptor）格式来表示系统物理内存布局。
    
    其具体表示如下：
        Offset  Size    Description
        00h     8字节   base address               #系统内存块基地址
        08h     8字节   length in bytes            #系统内存大小
        10h     4字节   type of address range      #内存类型
    
    看下面的 系统内存映射地址类型
        Values for System Memory Map address type:
        type = 1 01h    memory, available to OS，是可以使用的物理内存空间
        type = 2 02h    reserved, not available (e.g. system ROM, memory-mapped device)
                        保留，不能使用的物理内存空间，
                        这些地址不能映射到物理内存上， 但它们可以映射到ROM或者映射到其他设备，比如各种外设等。
        type = 3 03h    ACPI Reclaim Memory (usable by OS after reading ACPI tables)
        type = 4 04h    ACPI NVS Memory (OS is required to save this memory between NVS sessions)
                 other  not defined yet -- treat as Reserved
    
    INT15h BIOS中断的详细调用参数:
        eax：e820h：INT 15的中断调用参数；
        edx：534D4150h (即4个ASCII字符“SMAP”) ，这只是一个签名而已；
        ebx：如果是第一次调用或内存区域扫描完毕，则为0。 如果不是，则存放上次调用之后的计数值；
        ecx：保存地址范围描述符的内存大小,应该大于等于20字节；
        es:di：指向保存地址范围描述符结构的缓冲区，BIOS把信息写入这个结构的起始地址。

    此中断的返回值为:
        eflags的CF位：若INT 15中断执行成功，则不置位，否则置位；
        eax：534D4150h ('SMAP') ；
        es:di：指向保存地址范围描述符的缓冲区,此时缓冲区内的数据已由BIOS填写完毕
        ebx：下一个地址范围描述符的计数地址
        ecx    ：返回BIOS往ES:DI处写的地址范围描述符的字节大小
        ah：失败时保存出错代码
        
    这样，我们通过调用INT 15h BIOS中断，递增di的值（20的倍数），
    让BIOS帮我们查找出一个一个的内存布局entry，
    并放入到一个保存地址范围描述符结构的 缓冲区 中，
    供后续的ucore进一步进行物理内存管理。
    
    这个缓冲区结构定义在memlayout.h中：
```c
    /* memlayout.h */
    struct e820map {
    int nr_map;
    struct {
        long long addr;
        long long size;
        long type;
    } map[E820MAX];
    };
```
    
    bootasm.S 需要做的修改，再使能A20之后，线进行物理内存的探测保存一些信息后，再加载全局描述符表后进入保护模式。
```asm
# bootasm.S
# 2. 物理内存探测  通过 BIOS 中断获取内存布局
# 第一步： 设置一个存放内存映射地址描述符的物理地址(这里是0x8000)
probe_memory:
    # 在0x8000处存放struct e820map, 并清除e820map中的nr_map 
    movl $0, 0x8000 # 对0x8000处的32位单元清零,即给位于0x8000处的struct e820map的成员变量nr_map清零
    xorl %ebx, %ebx
    # 0x8004处将用于存放第一个内存映射地址描述符 
    movw $0x8004, %di # 表示设置调用INT 15h BIOS中断后，BIOS返回的映射地址描述符的起始地址
# 第二步： 将e820作为参数传递给INT 15h中断
start_probe:
    # 传入0xe820作为INT 15h中断的参数 
    movl $0xE820, %eax  #  INT 15的中断调用参数
    # 内存映射地址描述符的大小 
    movl $20, %ecx   # 设置地址范围描述符的大小为20字节，其大小等于struct e820map的成员变量map的大小
    movl $SMAP, %edx # 设置edx为534D4150h (即4个ASCII字符“SMAP”)，这是一个约定
    # 调用INT 15h中断 
    int $0x15 # 要求BIOS返回一个用地址范围描述符表示的内存段信息
# 通过检测eflags的CF位来判断探测是否结束。
# 如果没有结束， 设置存放下一个内存映射地址描述符的物理地址，然后跳到步骤2；如果结束，则程序结束
    # 如果eflags的CF位为0，则表示还有内存段需要探测 
    jnc cont
    movw $12345, 0x8000
    jmp finish_probe
cont:
    # 继续探测 设置下一个内存映射地址描述符的起始地址 
    addw $20, %di   # 设置下一个BIOS返回的映射地址描述符的起始地址
    # e820map中的nr_map加1 
    incl 0x8000 # 递增struct e820map的成员变量nr_map
    # 如果还有内存段需要探测则继续探测, 否则结束探测 
    cmpl $0, %ebx
    jnz start_probe
finish_probe:
```
    
    上述代码正常执行完毕后，
    在0x8000地址处保存了从BIOS中获得的内存分布信息，此信息按照struct e820map的设置来进行填充。
    这部分信息将在bootloader启动ucore后，
    由ucore的 page_init函数 来根据 struct e820map的memmap（定义了起始地址为0x8000）
    来完成对整个机器中的物理内存的总体管理。
    
## 物理内存空间管理的初始化
    当我们在bootloader中完成对物理内存空间的探测后， 
    我们就可以根据得到的信息来对可用的内存空间进行管理。
    在ucore中， 我们将物理内存空间按照页的大小(4KB)进行管理， 
    页的信息用Page这个结构体来保存。
    对整个计算机的每一个物理页的属性用结构Page.
    Page的定义在kern/mm/memlayout.h中。以页为单位的物理内存分配管理的实现在kern/default_pmm.[ch].
```c
struct Page {
    int ref;        // 映射此物理页的虚拟页个数 表示这页被页表的引用记数 page frame's reference counter
    uint32_t flags; // 描述物理页属性的flags array of flags that describe the status of the page frame
    unsigned int property;// 优先权 the num of free block, used in first fit pm manager
    list_entry_t page_link;// 双向链接各个Page结构的page_link双向链表  free list link
};
```
## 物理内存空间管理的初始化的过程
物理内存空间的初始化可以分为以下4步：

    1. 根据物理内存空间探测的结果， 找到最后一个可用空间的结束地址(或者Kernel的结束地址，选一个小的)，
       根据这个结束地址计算出整个可用的物理内存空间一共有多少个页。
    2. 找到Kernel的结束地址(end)，这个地址是在kernel.ld中定义的， 
       我们从这个地址所在的下一个页开始(pages)写入系统页的信息(将所有的Page写入这个地址)。
    3. 从pages开始，将所有页的信息的flag都设置为reserved(不可用)。
    4. 找到free页的开始地址， 并初始化所有free页的信息(free页就是除了kernel和页信息外的可用空间，
       初始化的过程会reset flag中的reserved位)。
       
     上面这几部中提到了很多地址空间， 下面我用一幅图来说明：   
![](https://sfault-image.b0.upaiyun.com/295/946/295946239-592131eae426e_articlex)

    end指的就是BSS的结束处；
    pages指的是BSS结束处 - 空闲内存空间的起始地址；
    free页是从空闲内存空间的起始地址 - 实际物理内存空间结束地址。

    有了这幅图，这些地址就很容易理解了。 

    物理页数数量：
        我们首先根据bootloader给出的内存布局信息找出最大的物理内存地址maxpa（定义在page_init函数中的局部变量），
        由于x86的起始物理内存地址为0，所以可以得知需要管理的物理页个数为：
        npage = maxpa / PGSIZE

    内存管理结构体page需要的内存数量：
        这样，我们就可以预估出管理页级物理内存空间所需的Page结构的内存空间所需的内存大小为：
        sizeof(struct Page) * npage

    内存管理处的起始管理结构体page：
        由于bootloader加载ucore的结束地址（用全局指针变量end记录）以上的空间没有被使用，
        所以我们可以把end按页大小为边界取整后，作为管理页级物理内存空间所需的Page结构的内存空间，记为：
        pages = (struct Page *)ROUNDUP((void *)end, PGSIZE);

    空闲物理空间起始地址 free：
        内存管理处的起始地址page + 内存管理所需的内存数量，之后为空闲地址。
        uintptr_t freemem = PADDR((uintptr_t)pages + sizeof(struct Page) * npage);

    标记内存管理page：
        for (i = 0; i < npage; i ++) {
             SetPageReserved(pages + i);
      // 只需把物理地址对应的Page结构中的flags标志设置为PG_reserved ，表示这些页已经被使用了，将来不能被用于分配。
        }

    标记空闲物理空间：
        //获得空闲空间的起始地址begin和结束地址end
        ...
        init_memmap(pa2page(begin), (end - begin) / PGSIZE);
        // 是把空闲物理页对应的Page结构中的flags和引用计数ref清零，
        // 并加到free_area.free_list指向的双向列表中，为将来的空闲页管理做好初始化准备工作。
        // 从pages开始保存了所有物理页的信息(严格来讲， 在pages处保存的npage个页的信息并不一定是所有的物理页信息，
        // 它还包括各种外设地址，ROM地址等。不过因为它包含了所有可用free页的信息，我们就可以使用pages来找到任何free页的信息)。 
        // 那如何将free页的信息和free页联系起来呢？很简单， 我们用地址的物理页号(pa的高20bit)作为index来定位free页的信息。
        // 因为pages处保存了系统中的第一个物理页的页信息，只要我们知道某个页的物理地址， 我们就可以很容易的找到它的页号(pa >> 12)。 
        // 有了页号，我们就可以通过pages[页号]来定位其页的信息了。在本lab中， 获取页的信息是由 pa2page() 来完成的。
        // 在初始化free页的信息时， 我们只将连续多个free页中第一个页的信息连入free_list中， 
        // 并且只将这个页的property设置为连续多个free页的个数。 其他所有页的信息我们只是简单的设置为0。

        相应的实现在default_pmm.c中的default_alloc_pages函数和default_free_pages函数，
        相关实现很简单，这里就不具体分析了，直接看源码，应该很好理解。
    物理内存页管理器框架: 

        在内存分配和释放方面最主要的作用是建立了一个物理内存页管理器框架，这实际上是一个函数指针列表，定义如下：
```c
struct pmm_manager {
            const char *name;    //物理内存页管理器的名字
            void (*init)(void);  //初始化内存管理器
            void (*init_memmap)(struct Page *base, size_t n); //初始化管理空闲内存页的数据结构
            struct Page *(*alloc_pages)(size_t n);            //分配n个物理内存页
            void (*free_pages)(struct Page *base, size_t n);  //释放n个物理内存页
            size_t (*nr_free_pages)(void);                    //返回当前剩余的空闲页数
            void (*check)(void); //用于检测分配/释放实现是否正确的辅助函数
};
```
    
    重点是实现init_memmap/ alloc_pages/ free_pages这三个函数。


## 内存段页式管理
    这个lab中最重要的一个知识点就是内存的段页式管理。 
    下图是段页式内存管理的示意图：
![](https://sfault-image.b0.upaiyun.com/419/087/4190879442-592131eaad948_articlex)
    
    我们可以看到，在这种模式下，
    逻辑地址先通过段机制转化成线性地址， 
    然后通过两种页表(页目录和页表)来实现线性地址到物理地址的转换。 
    有一点需要注意，在页目录和页表中存放的地址都是物理地址。
    
    下面是页目录表项：
![](https://sfault-image.b0.upaiyun.com/122/930/1229303217-5921324e8c4ef_articlex)
    
    下面是页表表项:
![](https://sfault-image.b0.upaiyun.com/386/565/3865659503-5921324e5d6d9_articlex)
    
    在X86系统中，页目录表的起始物理地址存放在cr3 寄存器中， 
    这个地址必须是一个页对齐的地址，也就是低 12 位必须为0。在ucore 用boot_cr3（mm/pmm.c）记录这个值。
    
    在ucore中，线性地址的的高10位作为页目录表的索引，之后的10位作为页表的的索引，
    所以页目录表和页表中各有1024个项，每个项占4B，所以页目录表和页表刚好可以用一个物理的页来存放。
    
    

    
    
    
    

