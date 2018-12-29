# python数据结构和算法
[参考](https://github.com/facert/python-data-structure-cn)

      计算机科学是解决问题的研究。
      计算机科学使用抽象作为表示过程和数据的工具。
      抽象的数据类型允许程序员通过隐藏数据的细节来管理问题领域的复杂性。
      Python是一种强大但易于使用的面向对象语言。
      列表、元组和字符串都是用Python有序集合构建的。
      字典和集合是无序的数据集合。
      类允许程序员实现抽象的数据类型。
      程序员可以重写标准方法，并创建新的方法。
      类可以被组织成层次结构。
      类构造器应该总是调用其父节点的构造函数，然后继续使用自己的数据和行为。
      
# 一、基本概念
      
## 1. 时间复杂度分析

算法计时 time模块，与算法复杂度 O()
```python
import time

def sumOfN2(n):
    start = time.time() # 计时开始
    
    theSum = 0 # 初始值
    for i in range(1,n+1):
        theSum = theSum + i # 叠加到累加器上 n(n+1)/2
        # n越大，计算时间越长，O(n)的 复杂度
    
    # 利用封闭方程而不是迭代来计算前n个整数的和
    # theSum =  n*(n+1)/2 # 该方法的计算时间 与 n 的大小无关
    # O(1)的复杂度
    
    end = time.time() #计时结束
    
    # 包含了执行结果和执行消耗时间的元组（tuple）
    return theSum, end-start

for i in range(5):
    print("Sum is %d required %10.7f seconds"%sumOfN(10000))
    
>>> 
Sum is 50005000 required  0.0018950 seconds
Sum is 50005000 required  0.0018620 seconds
Sum is 50005000 required  0.0019171 seconds
Sum is 50005000 required  0.0019162 seconds
Sum is 50005000 required  0.0019360 seconds

O(1)        常量
O(log(n))   对数复杂度
O(n)        线性 
O(n*log(n)) 线性 对数    
O(n^2)      平方
O(n^3)      立方
O(2^n)      指数   


```

![](https://facert.gitbooks.io/python-data-structure-cn/2.%E7%AE%97%E6%B3%95%E5%88%86%E6%9E%90/2.3.%E5%A4%A7O%E7%AC%A6%E5%8F%B7/assets/newplot.png)




## 2. 乱序单词检测
1. 先排序，后比较
```python
def anagramSolution2(s1,s2):
    # 字符串转换成列表
    alist1 = list(s1)
    alist2 = list(s2)
    # 对列表字母 进行排序
    alist1.sort() # 复杂度  O(n*log(n))===
    alist2.sort()

    pos = 0
    matches = True
    
    # 比对两个有序 列表是否相同  # 复杂度O(n)====
    while pos < len(s1) and matches:
        if alist1[pos]==alist2[pos]:
            pos = pos + 1 # 相同，再查看下一个字符
        else:
            matches = False #不相同，非乱序单词

    return matches

print(anagramSolution2('abcde','edcba'))

# 总复杂度 : O(n*log(n))

```

2. 以空间换时间，生成直方图，比较直方图
```python
def anagramSolution4(s1,s2):
    
    # 小写字母 共26个
    c1 = [0]*26 # 两个单词的 字母直方图 记录
    c2 = [0]*26
    
    # 生成 字符串1 的 字母直方图  O(n)
    for i in range(len(s1)):
        pos = ord(s1[i])-ord('a') # 减去最小字母的 ascii码，之后就变成直方图bin的位置 0~25
        c1[pos] = c1[pos] + 1 # 对应bin位置 计数+1
        
    # 生成 字符串2 的 字母直方图  O(n)
    for i in range(len(s2)):
        pos = ord(s2[i])-ord('a')
        c2[pos] = c2[pos] + 1
    
    # 比对两字符串对应 的 字母直方图 是否相同  O(26)
    j = 0
    stillOK = True
    while j<26 and stillOK:
        if c1[j]==c2[j]:
            j = j + 1
        else:
            stillOK = False

    return stillOK

print(anagramSolution4('apple','pleap'))

# 总复杂度 O(n)

```

## 3. 列表 的构造速度
```python
# 拼接
def test1():
    l = []
    for i in range(1000):
        l = l + [i]

def test2():
    l = []
    for i in range(1000):
        l.append(i) # 插入

def test3():
    l = [i for i in range(1000)] # 列表推导，列表生成器

def test4():
    l = list(range(1000)) # 调用 列表 构造函数 包装 range 函数

# 测试 timeit 模块 计时
t1 = Timer("test1()", "from __main__ import test1")
print("concat ",t1.timeit(number=1000), "milliseconds")

t2 = Timer("test2()", "from __main__ import test2")
print("append ",t2.timeit(number=1000), "milliseconds")
t3 = Timer("test3()", "from __main__ import test3")
print("comprehension ",t3.timeit(number=1000), "milliseconds")
t4 = Timer("test4()", "from __main__ import test4")
print("list range ",t4.timeit(number=1000), "milliseconds")

# from __main__ import test1 从 __main__ 命名空间导入到 timeit 设置的命名空间中。
# timeit 这么做是因为它想在一个干净的环境中做测试，而不会因为可能有你创建的任何杂变量，
# 以一种不可预见的方式干扰你函数的性能

>>>>>>
concat  6.54352807999 milliseconds
append  0.306292057037 milliseconds
comprehension  0.147661924362 milliseconds
list range  0.0655000209808 milliseconds   

append 操作比拼接快得多, 列表生成器的速度是 append 的两倍。

```

列表元素弹出性能记录
```python
# 从列表末尾处弹出所需时间将保持不变，即使列表不断增长。
popzero = timeit.Timer("x.pop(0)",
                       "from __main__ import x")
                       
# 从列表开始处弹出元素时间将随列表增长而增加   
popend = timeit.Timer("x.pop()",
                      "from __main__ import x")

x = list(range(2000000))
popzero.timeit(number=1000) # 传入测试次数

4.8213560581207275

x = list(range(2000000))
popend.timeit(number=1000)

0.0003161430358886719

```

## 4. 字典 相关的速度测试
字典和列表不同，你可以通过键而不是位置来访问字典中的项目。

```python
#  contains 操作 List 和 Dict 时间复杂性
import timeit
import random

for i in range(10000,1000001,20000):
    
    # i 在 x 中吗？操作，时间测试
    t = timeit.Timer("random.randrange(%d) in x"%i,
                     "from __main__ import random,x")
                     
    # 列表测试
    x = list(range(i))
    lst_time = t.timeit(number=1000)# 测试1000次??
    
    # 字典测试
    x = {j:None for j in range(i)}
    d_time = t.timeit(number=1000)
    
    # 打印两种时间
    print("%d,%10.3f,%10.3f" % (i, lst_time, d_time))


# 字典中的 contains 运算符的时间是恒定的，即使字典大小不断增长。
# 列表上的contains运算符所花费的时间与列表的大小成线性增长。

```


# 二、线性数据结构
      理解抽象数据类型的栈，队列，deque 和 列表。
      能够使用 Python 列表实现 ADT 堆栈，队列和 deque。
      了解基本线性数据结构实现的性能。
      了解前缀，中缀和后缀表达式格式。
      使用栈来实现后缀表达式。
      使用栈将表达式从中缀转换为后缀。
      使用队列进行基本时序仿真。
      能够识别问题中栈，队列和 deques 数据结构的适当使用。
      能够使用节点和引用将抽象数据类型列表实现为链表。
      能够比较我们的链表实现与 Python 的列表实现的性能。


      栈，队列，deques, 列表 是一类数据的容器，
      
      它们数据项之间的顺序由添加或删除的顺序决定。
      一旦一个数据项被添加，它相对于前后元素一直保持该位置不变。诸如此类的数据结构被称为线性数据结构。

      线性数据结构有两端，有时被称为左右，某些情况被称为前后。你也可以称为顶部和底部，名字都不重要。
      将两个线性数据结构区分开的方法是添加和移除项的方式，特别是添加和移除项的位置。
      例如一些结构允许从一端添加项，另一些允许从另一端移除项。
      这些变种的形式产生了计算机科学最有用的数据结构。
      他们出现在各种算法中，并可以用于解决很多重要的问题。

## 1. 栈
      栈（stack）又名堆栈，（有时称为“先进后出栈FILO”  后进先出LIFO ）是一个项的有序集合，其中添加移除新项总发生在同一端。
      这一端通常称为“顶部”。
      与顶部对应的端称为“底部”。
      
      先进入的数据被压入栈底，最后的数据在栈顶，需要读数据的时候从栈顶开始弹出数据（最后一个数据被第一个读出来）。
      栈具有记忆作用，对栈的插入与删除操作中，不需要改变栈底指针。
      
      向一个栈插入新元素又称作进栈、入栈或压栈，
      它是把新元素放到栈顶元素的上面，使之成为新的栈顶元素；
      从一个栈删除元素又称作 出栈 或 退栈，它是把栈顶元素删除掉，
      使其相邻的元素成为新的栈顶元素。
      
      栈的例子很常见。几乎所有的自助餐厅都有一堆托盘或盘子，你从顶部拿一个，就会有一个新的托盘给下一个客人。
      想象桌上有一堆书, 只有顶部的那本书封面可见，要看到其他书的封面，只有先移除他们上面的书。
![](https://facert.gitbooks.io/python-data-structure-cn/3.%E5%9F%BA%E6%9C%AC%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/3.3.%E4%BB%80%E4%B9%88%E6%98%AF%E6%A0%88/assets/3.3.%E4%BB%80%E4%B9%88%E6%98%AF%E6%A0%88.png)
      
      栈之所以重要是因为它能反转项的顺序。
      插入跟删除顺序相反.
      
      你可以想到使用计算机的时候所碰到的例子。
      
      例如，每个 web 浏览器都有一个返回按钮。
      当你浏览网页时，这些网页被放置在一个栈中（实际是网页的网址）。
      你现在查看的网页在顶部，你第一个查看的网页在底部。
      如果按‘返回’按钮，将按相反的顺序浏览刚才的页面。
      
### 栈的抽象数据类型
    栈是有序的 LIFO 。
    栈操作如下。
      Stack()    创建一个空的新栈。 
                 它不需要参数，并返回一个空栈。
      push(item) 将一个新项添加到栈的顶部。           入栈
                 它需要 item 做参数并不返回任何内容。
      pop()      从栈中删除顶部项。                  出栈
                 它不需要参数并返回 item 。
                 栈被修改。
      peek()    从栈返回顶部项，但不会删除它。        把脉，看一眼顶端元素
                 不需要参数。 
                 不修改栈。
      isEmpty()  测试栈是否为空。
                 不需要参数，并返回布尔值。
      size()     返回栈中的 item 数量。不
                 需要参数，并返回一个整数。   
      
举例：
     
     s 是已经创建的空栈，Table1 展示了栈操作序列的结果。
     栈中，顶部项 列在最右边，栈底在左边
     
     操作              栈内容             返回
     s.isEmpty()       []                True
     s.push(4)         [4]
     s.push('dog')     [4,'dog'] 
     s.peek()          [4,'dog']         'dog'
     s.push(True)      [4,'dog',True]
     s.size()          [4,'dog',True]    3
     s.isEmpty()       [4,'dog',True]    False
     s.push(8.4)       [4,'dog',True,8.4]
     s.pop()           [4,'dog',True]    8.4
     s.pop()           [4,'dog']         True
     s.size()          [4,'dog']         2
     
### python 实现栈
      回想一下，当我们给抽象数据类型一个物理实现时，我们将实现称为数据结构。
      抽象数据类型（如栈）的选择的实现是创建一个新类。
      栈操作实现为类的方法。
      此外，为了实现作为元素集合的栈，使用由 Python 提供的原语集合的能力是有意义的。 
      我们将使用 列表 作为底层实现。
     
     
      Python 中的列表类提供了有序集合机制和一组方法。
      例如，如果我们有列表 [2,5,3,6,7,4]，我们只需要确定列表的哪一端将被认为是栈的顶部。
      一旦确定，可以使用诸如 append 和 pop 的列表方法来实现操作。
      
      以下栈实现（ActiveCode 1）假定列表的结尾将保存栈的顶部元素。
      随着栈增长（push 操作），新项将被添加到列表的末尾。 
      pop 也操作列表末尾的元素。       
      
```python
class Stack:
     # 类初始化函数
     def __init__(self):
         self.items = [] # 初始化空列表
     
     # 是否为空
     def isEmpty(self):
         return self.items == []
     
     # 入栈，直接放入 列表尾部
     def push(self, item):
         self.items.append(item)
     
     # 出栈，列表 删除并范围 尾部元素
     def pop(self):
         return self.items.pop()
     
     # 看一眼列表尾部元素
     def peek(self):
         return self.items[len(self.items)-1]
     
     # 栈大小
     def size(self):
         return len(self.items)
         
# 使用栈 
# Stack 类的定义是从 pythonds 模块导入的
# 也可以直接使用上面的

from pythonds.basic.stack import Stack

s=Stack()

print(s.isEmpty())
s.push(4)
s.push('dog')
print(s.peek())
s.push(True)
print(s.size())
print(s.isEmpty())
s.push(8.4)
print(s.pop())
print(s.pop())
print(s.size())

```

### 栈应用1：简单括号 () 单一圆括号匹配
      区分括号是否匹配的能力是识别很多编程语言结构的重要部分。
      具有挑战的是如何编写一个算法，能够从左到右读取一串符号，并决定符号是否平衡。
      为了解决这个问题，我们需要做一个重要的观察。从左到右处理符号时，
      最近开始符号必须与下一个关闭符号相匹配。
      此外，处理的第一个开始符号必须等待直到其匹配最后一个符号。
      结束符号以相反的顺序匹配开始符号。
      他们从内到外匹配。
      这是一个可以用栈解决问题的线索。
```python
from pythonds.basic.stack import Stack

def parChecker(symbolString):
    # 创建栈
    s = Stack()
    # 平衡标志
    balanced = True
    
    index = 0
    
    while index < len(symbolString) and balanced:
        # 当前 字符
        symbol = symbolString[index]
        
        # 是起始 括号
        if symbol == "(":
            s.push(symbol) # 入栈
            
        # 那就是 结尾括号 ")"    
        else:
            if s.isEmpty():
                # 无 起始括号，则，不平衡
                balanced = False
            # 已经有 起始括号了
            # 弹出最近入栈的 一个 起始括号
            else:
                s.pop()
        
        # 处理下一个字符
        index = index + 1
    
    # 最后 平衡，且 栈为空了
    if balanced and s.isEmpty():
        return True # 则是平衡的
    else:
        # 栈内还有 起始括号，或者多余 结束括号，都是不平衡的
        return False

print(parChecker('((()))'))
print(parChecker('(()'))


```

### 栈应用2：符号匹配 圆括号() 方括号[] 花括号{} 匹配  
      在 Python 中，
      方括号 [ 和 ] 用于列表，
      花括号 { 和 } 用于字典。
      圆括号 ( 和 ) 用于元组和算术表达式。
      只要每个符号都能保持自己的开始和结束关系，就可以混合符号。
      
      符号字符串如
      { { ( [ ] [ ] ) } ( ) }
      
      不仅每个开始符号都有对应的结束符号，而且符号的类型也匹配。
      上节的简单括号检查程序可以轻松的扩展处理这些新类型的符号。
      
      每个开始符号被简单的压入栈中，等待匹配的结束符号出现。
      当出现结束符号时，唯一的区别是我们必须检查确保它正确匹配栈顶部开始符号的类型。
      如果两个符号不匹配，则字符串不匹配。
      如果整个字符串都被处理完并且没有什么留在栈中，则字符串匹配。
      
```python
from pythonds.basic.stack import Stack

def parChecker(symbolString):
    # 空栈，用于存储 三种开始 字符
    s = Stack()
    balanced = True # 平衡标志
    index = 0
    
    while index < len(symbolString) and balanced:
        # 当前字符
        symbol = symbolString[index]
        
        # 是三种开始字符 中的一种
        if symbol in "([{":
            s.push(symbol)
        
        # 否者 为三种 结束字符 中的一种
        else:
            if s.isEmpty():
                # 无开始字符，来匹配结束字符，则不平衡
                balanced = False
            else:
                top = s.pop() # 弹出最近的开始字符
                # 查看是否 与 该 结束字符 匹配
                if not matches(top,symbol):
                    # 不匹配，则 不平衡
                    balanced = False
        # 检查下一个字符
        index = index + 1
        
    if balanced and s.isEmpty():
        # 平衡，且已无 开始字符
        return True
    # 不平衡，或 还有剩余开始字符未匹配到 结束字符
    else:
        return False

# 开始字符 open 与 结束字符 close 是否匹配
def matches(open,close):
    opens   = "([{"
    closers = ")]}"
    # 对应字符索引，相同的话，就匹配
    return opens.index(open) == closers.index(close)


print(parChecker('{{([][])}()}'))
print(parChecker('[{()]'))

```


### 栈应用3：十进制转换成二进制
      二进制在计算机科学中是很重要的，因为存储在计算机内的所有值都是以 0 和 1 存储的。
      如果没有能力在二进制数和普通字符串之间转换，我们与计算机之间的交互非常棘手。
      
      如何能够容易地将整数值转换为二进制呢？
          答案是“除 2”算法，它用栈来跟踪二进制结果的数字。
      “除 2” 算法假定我们从大于 0 的整数开始。不断迭代的将十进制除以 2，并跟踪余数。
      第一个除以 2 的余数说明了这个值是偶数还是奇数。偶数有 0 的余数，记为 0。
      奇数有余数 1，记为 1.我们将得到的二进制构建为数字序列，第一个余数实际上是序列中的最后一个数字。
      我们再次看到了反转的属性，表示栈可能是解决这个问题的数据结构。
![](https://facert.gitbooks.io/python-data-structure-cn/3.%E5%9F%BA%E6%9C%AC%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/3.8.%E5%8D%81%E8%BF%9B%E5%88%B6%E8%BD%AC%E6%8D%A2%E6%88%90%E4%BA%8C%E8%BF%9B%E5%88%B6/assets/3.8.%E5%8D%81%E8%BF%9B%E5%88%B6%E8%BD%AC%E6%8D%A2%E6%88%90%E4%BA%8C%E8%BF%9B%E5%88%B6.figure5.png)
      
```python
from pythonds.basic.stack import Stack

def divideBy2(decNumber):
    # 空栈，记录二进制串码
    remstack = Stack()

    while decNumber > 0:
        rem = decNumber % 2 # 除以二，取余数
        remstack.push(rem)  # 余数进栈
        # 使用商，继续循环
        decNumber = decNumber // 2
    
    # 生成二进制串码
    # 栈顶，最后入栈的，为二进制串码的 高位(左边)
    binString = ""
    while not remstack.isEmpty():
        # 依次出栈，转换成字符串后，连接在一起
        binString = binString + str(remstack.pop())
    # 返回生成的 二进制串码
    return binString

print(divideBy2(42))


'''
可以修改 divideBy2 函数，使它不仅能接受十进制参数，还能接受预期转换的基数。
‘除 2’ 的概念被简单的替换成更通用的 ‘除基数’。
下面展示的是一个名为 baseConverter 函数。
采用十进制数和 2 到 16 之间的任何基数作为参数。
余数部分仍然入栈，直到被转换的值为 0。
我们创建一组数字，用来表示超过 9 的余数。
'''

# 输入十进制数 和 目标基底数串
# 也可以改进，传入一个 指定基底的子串(计算得到十进制数后，再使用 除基底法)，和目标基底
def baseConverter(decNumber,base):
    # 0~15的余数
    digits = "0123456789ABCDEF"
    
    # 空栈记录余数
    remstack = Stack()

    while decNumber > 0:
        rem = decNumber % base # 十进制数 取余 基底数 得到余数
        remstack.push(rem)     # 栈记录 余数
        decNumber = decNumber // base  # 使用 商

    newString = ""
    while not remstack.isEmpty():
        # 余数依次出栈，转换成字符串后，连接在一起
        newString = newString + digits[remstack.pop()]
        
    return newString

print(baseConverter(25,2))
print(baseConverter(25,16))


```

### 栈应用4： 中缀，前缀和后缀表达式
      算术表达式如 B*C，乘法运算符 * 出现在表达式中。
      这种类型的符号称为中缀，因为运算符在它处理的两个操作数之间。
      看另外一个中缀示例，A+B*C，运算符 + 和 * 仍然出现在操作数之间。
      这里面有个问题是，他们分别作用于哪个运算数上，
      + 作用于 A 和 B , 还是 * 作用于 B 和 C？表达式似乎有点模糊。
      
      每个运算符都有一个优先级。
      优先级较高的运算符在优先级较低的运算符之前使用。
      
      唯一改变顺序的是括号的存在。
      
      算术运算符的优先顺序是将乘法和除法置于加法和减法之上。
      
      如果出现具有相等优先级的两个运算符，则使用从左到右的顺序排序或关联。
      
      例如：
      A+B*C， B 和 C 首先相乘，然后将 A 与该结果相加。
      (A+B)*C 将强制在乘法之前执行 A 和 B 的加法。
      在表达式 A+B+C 中，最左边的 + 首先使用。
      
      计算机需要准确知道要执行的操作符和顺序。
      一种保证不会对操作顺序产生混淆的表达式的方法是创建一个称为完全括号表达式的表达式。
      这种类型的表达式对每个运算符都使用一对括号。
      括号没有歧义的指示操作的顺序。
      也没有必要记住任何优先规则。
      
      表达式 A+B*C+D 可以重写为 ((A + (B * C)) + D) ，表明先乘法，然后是左边的加法。
      A + B + C + D 可以写为 (((A + B) + C) + D)，因为加法操作从左向右相关联。
      
      中缀表达式 A+B, 如果我们移动两个操作数之间的运算符会发生什么？结果表达式变成 + A B。
      同样，我们也可以将运算符移动到结尾，得到 A B + ，这样看起来有点奇怪。
      
      改变操作符的位置得到了两种新的表达式格式，前缀和后缀。
      前缀表达式符号要求所有运算符在它们处理的两个操作数之前。
      另一个方面，后缀要求其操作符在相应的操作数之后。
                   前缀                        后缀
      A + B   ==> + A B                       A B +
      A + B * C => + A * B C                  A B C * +
      
      A + B * C + D => + + A * B C D          A B C * + D +
      
      (A + B) * C  => * + A B C               A B + C *
      (A + B) * (C + D)  => * + A B + C D     A B + C D + *
      A * B + C * D =>  + * A B * C D         A B * C D * +
      A + B + C + D =>  + + + A B C D         A B + C + D +  
      
      再次考虑表达式 A + B * C。
      如上所示，A B C * +是等价的后缀表达式。 
      我们已经注意到，操作数 A，B 和 C 保持在它们的相对位置。
      只有操作符改变位置。
      再看中缀表达式中的运算符。
      从左到右出现的第一个运算符为 +。 
      然而，在后缀表达式中，+ 在结束位置，因为下一个运算符 * 的优先级高于加法。
      原始表达式中的运算符的顺序在生成的后缀表达式中相反。（栈性质?）
      
      当我们处理表达式时，操作符必须保存在某处，因为它们相应的右操作数还没有看到。
      此外，这些保存的操作符的顺序可能由于它们的优先级而需要反转。
      这是在该示例中的加法和乘法的情况，由于加法运算符在乘法运算符之前，
      并且具有较低的优先级，因此需要在使用乘法运算符之后出现。 
      由于这种顺序的反转，考虑使用栈来保存运算符直到用到它们是有意义的。
      
      (A + B)* C的情况会是什么样呢？ 回想一下，A B + C *是等价的后缀表达式。
      从左到右处理此中缀表达式，我们先看到 +。 
      在这种情况下，当我们看到 *，+已经放置在结果表达式中，由于括号它的优先级高于*。
      我们现在可以开始看看转换算法如何工作。
      当我们看到左括号时，我们保存它，表示高优先级的另一个运算符将出现。
      该操作符需要等到相应的右括号出现以表示其位置（回忆完全括号的算法）。 
      当右括号出现时，可以从栈中弹出操作符。
      
      当我们从左到右扫描中缀表达式时，我们将使用栈来保留运算符。
      这将提供我们在第一个例子中注意到的反转。
      堆栈的顶部将始终是最近保存的运算符。
      每当我们读取一个新的运算符时，
      我们需要考虑该运算符如何与已经在栈上的运算符（如果有的话）比较优先级。
      
      假设中缀表达式是一个由空格分隔的标记字符串。 
      操作符标记是*，/，+和 - ，以及左右括号。
      操作数是单字符 A，B，C 等。 
      
      以下步骤将 生成一个 后缀顺序 字符串。
            1. 创建一个名为 opstack 的空栈以保存运算符。
               给输出创建一个空列表。
            2. 通过使用字符串方法拆分 将 输入的 中缀字符串 转换为 标记列表。
            3. 从左到右扫描标记列表。
               a. 如果标记 是 操作数，将其附加到输出 列表的末尾(操作数顺序不变)。
               b. 如果标记是左括号，将其压到 opstack 上。（起始括号入栈）
               c. 如果标记是右括号，则弹出 opstack，直到删除相应的左括号。
                  将每个运算符附加到输出列表的末尾（括号的优先级高）。
               d. 如果标记是运算符，*，/，+或 - ，将其压入 opstack。
                  但是，首先删除已经在 opstack 中具有更高 或 相等优先级的 任何运算符，并将它们加到输出列表中。

            4. 当输入表达式被完全处理时，检查 opstack。
               仍然在栈上的任何运算符都可以删除并加到输出列表的末尾。

![](https://facert.gitbooks.io/python-data-structure-cn/3.%E5%9F%BA%E6%9C%AC%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/3.9.%E4%B8%AD%E7%BC%80%E5%89%8D%E7%BC%80%E5%92%8C%E5%90%8E%E7%BC%80%E8%A1%A8%E8%BE%BE%E5%BC%8F/assets/3.9.%E4%B8%AD%E7%BC%80%E5%90%8E%E7%BC%80%E5%92%8C%E5%90%8E%E7%BC%80%E8%A1%A8%E8%BE%BE%E5%BC%8F.figure9.png)
      
      看到操作数A,直接放入输出列表尾部 [A]。
      看到第一个 * 时，入栈，看到操作数B 放入输出列表尾部 [A B]。
      在看到 + 运算符时，先删除栈中高优先级的运算符 *号，并把删除的运算符*号 放入 输出列表尾部 [A B *]，
            同时+号入栈
      看到操作数C 放入输出列表尾部 [A B * C]。
      看到第二个 * 出现时，+ 保留在栈中，因为乘法优先级高于加法，*号入栈。
      看到操作数D 放入输出列表尾部 [A B * C D]。
      弹出*号，放入输出列表尾部 [A B * C D *]。
      弹出+号，放入输出列表尾部 [A B * C D * +]。
      在中缀表达式的末尾，栈被弹出两次，删除两个运算符，并将 + 作为后缀表达式中的最后一个运算符。
      
```python
from pythonds.basic.stack import Stack

def infixToPostfix(infixexpr):
    # 使用一个名为 prec 的字典来保存操作符的优先级。
    # 这个字典将每个 运算符 映射 到一个整数
    prec = {}
    prec["*"] = 3 # 最高优先级
    prec["/"] = 3
    prec["+"] = 2
    prec["-"] = 2
    prec["("] = 1     
    # 左括号将赋予最低的值??。这样，与其进行比较的任何运算符将具有更高的优先级，将被放置在它的顶部。
    
    # 1. 运算符 记忆 括号 栈
    opStack = Stack()
    # 输出 后缀字符串 列表
    postfixList = []
    
    # 2. 输入表达式 按空格分割成 列表===
    tokenList = infixexpr.split()
    
    # 3. 遍历 表达式 列表
    for token in tokenList:
        # 3.a 大小字母 或 数字======
        if token in "ABCDEFGHIJKLMNOPQRSTUVWXYZ" or token in "0123456789":
            # 直接放入 输出 后缀字符串 列表 尾部
            postfixList.append(token)
        # 3.b 左括号，起始括号
        elif token == '(':
            opStack.push(token) # 左括号放入栈
        # 3.c 右括号    
        elif token == ')':
            # 保存运算符与括号的栈  出栈
            topToken = opStack.pop()
            while topToken != '(': 
                # 如果不是 左括号 直接放入  输出 后缀字符串 列表 尾部
                # 是括号内部的 运算符，优先放入 
                postfixList.append(topToken)
                # 弹出下一个栈元素
                topToken = opStack.pop()
        # 3.4 运算符
        else:
            while (not opStack.isEmpty()) and \
               (prec[opStack.peek()] >= prec[token]):
                # 当前栈顶元素 比 遍历到的 运算符 优先级高
                postfixList.append(opStack.pop()) # 将优先级高的 运算符直接放入到 后缀字符串 列表 尾部
            # 将当前  遍历到的 运算符 放入到 栈中
            opStack.push(token)
    
    # 4 最后 检查 opstack
    while not opStack.isEmpty():
        # 运算符 栈不空?
        # 删除运算符，并添加到 输出后缀字符串 列表 尾部
        postfixList.append(opStack.pop()) # 未考虑 括号不匹配的情况?????
    return " ".join(postfixList)

print(infixToPostfix("A * B + C * D"))
print(infixToPostfix("( A + B ) * C - ( D - E ) * ( F + G )"))

执行结果如下 

>>> infixtopostfix("( A + B ) * ( C + D )")
'A B + C D + *'
>>> infixtopostfix("( A + B ) * C")
'A B + C *'
>>> infixtopostfix("A + B * C")
'A B C * +'
>>>


# 利用栈 后缀表达式求值
'''
作为最后栈的示例，我们考虑对后缀符号中的表达式求值。
在这种情况下，栈再次是我们选择的数据结构。
但是，在扫描后缀表达式时，它必须等待操作数，而不像上面的转换算法中的运算符。
解决问题的另一种方法是，每当在输入上看到运算符时，计算两个最近的操作数。
要详细的了解这一点，考虑后缀表达式 4 5 6 * +， 首先遇到操作数 4 和 5，此时，
你还不确定如何处理它们，直到看到下一个符号。
将它们放置到栈上，确保它们在下一个操作符出现时可用。
在这种情况下，下一个符号是另一个操作数。所以，像先前一样，压入栈中。并检查下一个符号。
现在我们看到了操作符 *，这意味着需要将两个最近的操作数相乘。
通过弹出栈两次，我们可以得到正确的两个操作数，然后执行乘法（这种情况下结果为 30）。
我们现在可以通过将其放回栈中来处理此结果，以便它可以表示为表达式后面的运算符的操作数。
当处理最后一个操作符时，栈上只有一个值，弹出并返回它作为表达式的结果。
'''

```
![](https://facert.gitbooks.io/python-data-structure-cn/3.%E5%9F%BA%E6%9C%AC%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/3.9.%E4%B8%AD%E7%BC%80%E5%89%8D%E7%BC%80%E5%92%8C%E5%90%8E%E7%BC%80%E8%A1%A8%E8%BE%BE%E5%BC%8F/assets/3.9.%E4%B8%AD%E7%BC%80%E5%90%8E%E7%BC%80%E5%92%8C%E5%90%8E%E7%BC%80%E8%A1%A8%E8%BE%BE%E5%BC%8F.figure10.png)  
      
      
https://facert.gitbooks.io/python-data-structure-cn/3.%E5%9F%BA%E6%9C%AC%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/3.9.%E4%B8%AD%E7%BC%80%E5%89%8D%E7%BC%80%E5%92%8C%E5%90%8E%E7%BC%80%E8%A1%A8%E8%BE%BE%E5%BC%8F/
      
      
      
## 2. 队列




## 3. 双端队列 deques




## 4. 列表 List









