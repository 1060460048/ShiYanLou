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

7 8 + 3 2 + / 。
在这个例子中有两点需要注意，
首先，栈的大小增长收缩，然后再子表达式求值的时候再次增长。
第二，除法操作需要谨慎处理。回想下，后缀表达式的操作符顺序没变，仅仅改变操作符的位置。
当用于除法的操作符从栈中弹出时，它们被反转。
由于除法不是交换运算符，换句话说 15/5和 5/15 不同，
因此我们必须保证操作数的顺序不会交换。

假设后缀表达式是一个由空格分隔的标记字符串。 
运算符为*，/，+和 - ，操作数假定为单个整数值。
输出将是一个整数结果。

      1. 创建一个名为 operandStack 的空栈。
      2. 拆分字符串转换为标记列表。
      3. 从左到右扫描标记列表。
        3.1 如果标记是操作数，将其从字符串转换为整数，并将值压到operandStack。
        3.2 如果标记是运算符*，/，+或-，它将需要两个操作数。
            弹出operandStack 两次。 
            第一个弹出的是第二个操作数，第二个弹出的是第一个操作数。
            执行算术运算后，将结果压到操作数栈中。
      4. 当输入的表达式被完全处理后，结果就在栈上，弹出 operandStack 并返回值。

'''
from pythonds.basic.stack import Stack

# 计算 后缀表达式的值
def postfixEval(postfixExpr):
    #  1. 创建一个名为 operandStack 的空栈。
    operandStack = Stack()
    # 2. 拆分字符串转换为标记列表。
    tokenList = postfixExpr.split()
    # 3. 从左到右扫描标记列表。
    for token in tokenList:
        # 3.1 如果标记是操作数
        if token in "0123456789":
            # 将其从字符串转换为整数，并将值压到operandStack。
            operandStack.push(int(token))
        # 3.2 如果标记是运算符*，/，+或-
        else:
            # 第一个弹出的是第二个操作数
            operand2 = operandStack.pop()
            # 第二个弹出的是第一个操作数。
            operand1 = operandStack.pop()
            # 执行算术运算
            result = doMath(token,operand1,operand2)
            # 将结果压到操作数栈中
            operandStack.push(result)
    # 4. 当输入的表达式被完全处理后，结果就在栈上，弹出 operandStack 并返回值。
    return operandStack.pop()

# 它将获取两个操作数和运算符，执行相应的计算
def doMath(op, op1, op2):
    if op == "*":
        return op1 * op2
    elif op == "/":
        return op1 / op2
    elif op == "+":
        return op1 + op2
    else:
        return op1 - op2

print(postfixEval('7 8 + 3 2 + /'))

```
![](https://facert.gitbooks.io/python-data-structure-cn/3.%E5%9F%BA%E6%9C%AC%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/3.9.%E4%B8%AD%E7%BC%80%E5%89%8D%E7%BC%80%E5%92%8C%E5%90%8E%E7%BC%80%E8%A1%A8%E8%BE%BE%E5%BC%8F/assets/3.9.%E4%B8%AD%E7%BC%80%E5%90%8E%E7%BC%80%E5%92%8C%E5%90%8E%E7%BC%80%E8%A1%A8%E8%BE%BE%E5%BC%8F.figure10.png)  
      
      
![](https://facert.gitbooks.io/python-data-structure-cn/3.%E5%9F%BA%E6%9C%AC%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/3.9.%E4%B8%AD%E7%BC%80%E5%89%8D%E7%BC%80%E5%92%8C%E5%90%8E%E7%BC%80%E8%A1%A8%E8%BE%BE%E5%BC%8F/assets/3.9.%E4%B8%AD%E7%BC%80%E5%90%8E%E7%BC%80%E5%92%8C%E5%90%8E%E7%BC%80%E8%A1%A8%E8%BE%BE%E5%BC%8F.figure11.png)



## 2. 队列
      队列是项的有序结合，其中添加新项的一端称为队尾，移除项的一端称为队首。
      当一个元素从队尾进入队列时，一直向队首移动，直到它成为下一个需要移除的元素为止。
      最近添加的元素必须在队尾等待。
      集合中存活时间最长的元素在队首，这种排序成为 FIFO，先进先出，也被成为先到先得。
      
      队列的最简单的例子是我们平时不时会参与的列。
      排队等待电影，在杂货店的收营台等待，在自助餐厅排队等待（这样我们可以弹出托盘栈）。
      行为良好的线或队列是有限制的，因为它只有一条路，只有一条出路。
      不能插队，也不能离开。你只有等待了一定的时间才能到前面。
![](https://facert.gitbooks.io/python-data-structure-cn/3.%E5%9F%BA%E6%9C%AC%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/3.10.%E4%BB%80%E4%B9%88%E6%98%AF%E9%98%9F%E5%88%97/assets/3.10.%E4%BB%80%E4%B9%88%E6%98%AF%E9%98%9F%E5%88%97.figure1.png)
      
      12306网上订票排队。。。。
      除了打印机打印队列，操作系统使用多个不同的队列来控制计算机内的进程。
      下一步做什么的调度通常基于尽可能快地执行程序和尽可能多的服务用户的排队算法。
      此外，当我们敲击键盘时，有时屏幕上出现的字符会延迟。
      这是由于计算机在那一刻做其他工作。
      按键的内容被放置在类似队列的缓冲器中，使得它们最终可以以正确的顺序显示在屏幕上。
      
      
### 抽象数据类型
     队列被构造为在队尾添加项的有序集合，并且从队首移除。
     队列保持 FIFO 排序属性。
     队列操作如下。
     
      Queue()       创建一个空的新队列。 它不需要参数，并返回一个空队列。
      enqueue(item) 将新项添加到队尾。 它需要 item 作为参数，并不返回任何内容。
      dequeue()     从队首移除项。它不需要参数并返回 item。 队列被修改。
      isEmpty()     查看队列是否为空。它不需要参数，并返回布尔值。
      size()        返回队列中的项数。它不需要参数，并返回一个整数。
      
      作为示例，我们假设 q 是已经创建并且当前为空的队列。
         操作              队列状态             返回数据
         q.isEmpty()       []                  True        队列是否为空
         q.enqueue(4)      [4]                             队尾添加元素
         q.enqueue('dog')  ['dog',4]                       队尾添加元素
         q.enqueue(True)   [True,'dog',4]                  队尾添加元素
         q.size()          [True,'dog',4]      3           队列大小
         q.enqueue(8.4)    [8.4,True,'dog',4]              队尾添加元素
         q.dequeue()       [8.4,True,'dog']    4           队首删除元素
         q.dequeue()       [8.4,True]          'dog'       队首删除元素
         q.size()          [True,'dog']        2           队列大小
      
### Python实现队列
      实现队列抽象数据类型创建一个新类。
      和前面一样，我们将使用列表集合来作为构建队列的内部表示。
      我们需要确定列表的哪一端作为队首，哪一端作为队尾。
      假定队尾在列表中的位置为 0。
      这允许我们使用列表上的插入函数向队尾添加新元素。
      弹出操作可用于删除队首的元素（列表的最后一个元素）。
      回想一下，这也意味着入队为 O(n) ( 数据依次后移 )，出队为 O(1)。
      
```python

class Queue:
    def __init__(self):
        self.items = []

    def isEmpty(self):
        return self.items == []

    def enqueue(self, item):
        self.items.insert(0,item)

    def dequeue(self):
        return self.items.pop()

    def size(self):
        return len(self.items)


# 测试
进一步的操作这个队列产生如下结果：

q = Queue()
q.enqueue(4)
q.enqueue('dog')
q.enqueue(True)
q.size()
>>> 3
 q.isEmpty()
>>>False
q.enqueue(8.4)
q.dequeue()
>>> 4
q.dequeue()
>>> 'dog'
q.size()
>>> 2
```

### 队列应用1: 模拟：烫手山芋
      在这个游戏中，孩子们围成一个圈，并尽可能快的将一个山芋递给旁边的孩子。
      在某一个时间，动作结束，有山芋的孩子从圈中移除。
      游戏继续开始直到剩下最后一个孩子。
      
      这个游戏相当于著名的约瑟夫问题，一个一世纪著名历史学家弗拉维奥·约瑟夫斯的传奇故事。
      故事讲的是，他和他的 39 个战友被罗马军队包围在洞中。
      他们决定宁愿死，也不成为罗马人的奴隶。
      他们围成一个圈，其中一人被指定为第一个人，顺时针报数到第七人，就将他杀死。
      约瑟夫斯是一个成功的数学家，他立即想出了应该坐到哪才能成为最后一人。
      最后，他加入了罗马的一方，而不是杀了自己。
      你可以找到这个故事的不同版本，有些说是每次报数 3 个人，有人说允许最后一个人逃跑。
      无论如何，思想是一样的。
      
      我们的程序将输入名称列表和一个称为 num 常量用于报数(报到该数时，淘汰)。
      它将返回以 num 为单位重复报数后剩余的最后一个人的姓名。
      
      为了模拟这个圈，我们使用队列。假设拿着山芋的孩子在队列的前面。
      当拿到山芋的时候，这个孩子将先出列再入队列，把他放在队列的最后。
      经过 num 次的出队入队后，前面的孩子将被永久移除队列。
      并且另一个周期开始，继续此过程，直到只剩下一个名字（队列的大小为 1时）。
![](https://facert.gitbooks.io/python-data-structure-cn/3.%E5%9F%BA%E6%9C%AC%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/3.13.%E6%A8%A1%E6%8B%9F%EF%BC%9A%E7%83%AB%E6%89%8B%E5%B1%B1%E8%8A%8B/assets/3.13.%E6%A8%A1%E6%8B%9F%EF%BC%9A%E7%83%AB%E6%89%8B%E5%B1%B1%E8%8A%8B.figure3.png)
      
      
```python
from pythonds.basic.queue import Queue

# 传入一个名字列表，和报到的数
def hotPotato(namelist, num):
    # 1. 新建空队列====
    simqueue = Queue()
    # 2. 名字放入队列=====
    for name in namelist:
        simqueue.enqueue(name)
    
    # 3. 玩游戏，报数，淘汰，...
    while simqueue.size() > 1:
        for i in range(num):
            # 队首出队，队尾入队
            simqueue.enqueue(simqueue.dequeue())
        # 报数到 num时，只出队，被淘汰
        simqueue.dequeue()
    # 4. 还剩一个玩家时，游戏结束====
    return simqueue.dequeue()

print(hotPotato(["Bill","David","Susan","Jane","Kent","Brad"],7))
# 计数常数的值大于列表中的名称数。这不是一个问题，因为队列像一个圈，计数会重新回到开始，直到达到计数值。
# 另外，请注意，列表加载到队列中以使列表上的名字位于队列的前面。
# 在这种情况下，Bill 是列表中的第一个项，因此他在队列的前面。

```
      
      
      
###  队列应用2: 模拟： 打印机
      假设 平均 3分钟(180秒) 会有一个打印任务
      对于每一秒，我们可以通过生成 1 到 180 之间的随机数来模拟打印任务发生的机会。
      如果数字是 180，我们说一个任务已经创建。
      请注意，可能会在一下子创建许多任务，或者需要等待一段时间才有任务。
      这就是模拟的本质。
      
主要模拟步骤

      1. 创建打印任务的队列，每个任务都有个时间戳。队列启动的时候为空。
      2. 每秒（currentSecond）：
         2.1 是否创建新的打印任务？
             如果是，将 currentSecond 作为 时间戳 添加到 队列。
         2.2 如果 打印机 不忙 并且 有任务在等待（打印队列不空）
             从 打印机队列 中删除 一个任务 并将其分配给打印机
             从 currentSecond 中减去 该任务的时间戳，以计算 该任务 的 等待时间。
             将该任务的 等待时间 附加到列表中稍后处理。
             根据打印任务的页数，确定需要多少时间（所需处理时间）。
      3. 该任务的所需的等待时间 减去一秒。
      4. 如果任务已经完成，换句话说，所需的时间已经达到零，打印机空闲。
      模拟完成后，从生成的等待时间列表中计算平均等待时间。    

Python 实现

为了设计此模拟，我们将为上述三个真实世界对象创建类：

打印机(Printer), 打印任务(Task), 打印队列(PrintQueue)

```python
# 打印机(Printer)
class Printer:
    def __init__(self, ppm):
        self.pagerate = ppm     # 打印速度，页/每分钟
        self.currentTask = None # 当前是否有任务
        self.timeRemaining = 0  # 任务所需时间
    
    # 任务计时
    def tick(self):
        if self.currentTask != None:
            # 任务所需时间，每过一秒，任务时间-1
            self.timeRemaining = self.timeRemaining - 1
            if self.timeRemaining <= 0:
                # 任务已经完成，当前无任务
                self.currentTask = None

    def busy(self):
        if self.currentTask != None:
            return True # 无任务，空闲
        else:
            return False # 有任务
    
    # 添加一个任务
    def startNext(self,newtask):
        self.currentTask = newtask # 新任务
        # 根据任务的页数计算所需的时间
        self.timeRemaining = newtask.getPages() * 60/self.pagerate

# 生成打印任务(Task)====
# 创建任务时，随机数生成器将提供 1 到 20 页的长度
# 还需要保存一个时间戳用于计算等待时间
import random

class Task:
    def __init__(self,time):
        self.timestamp = time # 任务开始时间
        self.pages = random.randrange(1,21)# 任务量，打印页数

    def getStamp(self):
        return self.timestamp

    def getPages(self):
        return self.pages
    
    # 计算任务已经持续的时间
    def waitTime(self, currenttime):
        return currenttime - self.timestamp
        

#  整个仿真
from pythonds.basic.queue import Queue

import random

# 任务仿真
def simulation(numSeconds, pagesPerMinute):
    # 创建打印机 实例
    labprinter = Printer(pagesPerMinute) # 打印机速度 页/每分钟
    # 创建打印机队列实例
    printQueue = Queue()
    # 等待时间列表
    waitingtimes = []
    
    # 工作时间范围
    for currentSecond in range(numSeconds):
        # 该秒是否需要创建任务
        if newPrintTask():
            # 创建任务
            task = Task(currentSecond)
            # 把打印任务 加入打印机队列
            printQueue.enqueue(task)
            
        # 打印机不忙 并且 有打印任务
        if (not labprinter.busy()) and (not printQueue.isEmpty()):
            # 从队列中 取出一个打印任务
            nexttask = printQueue.dequeue()
            # 计算该任务 的等待时间
            waitingtimes.append(nexttask.waitTime(currentSecond))
            # 打印机开始下一个任务
            labprinter.startNext(nexttask)
            
        # 打印机工作，任务时间逐渐较少
        labprinter.tick()
    
    # 计算平均等待时间
    averageWait=sum(waitingtimes)/len(waitingtimes)
    # 大约
    print("Average Wait %6.2f secs %3d tasks remaining."%(averageWait,printQueue.size()))

# 每秒 根据生产的随机数决定是否需要产生打印任务，模拟打印任务生成
def newPrintTask():
    # 平均180秒生成一个任务
    # 每秒 生成1~180之间一个随机数，为180时，生成任务
    num = random.randrange(1,181)
    if num == 180:
        return True # 生成任务 标志为真
    else:
        return False

# 十次模型
for i in range(10):
    # 总时间 3600秒， 打印机速度 5页/每分钟 
    # 模拟 60 分钟（3,600秒）
    simulation(3600,5)
    
>>> 
Average Wait 165.38 secs 2 tasks remaining.
Average Wait  95.07 secs 1 tasks remaining.
Average Wait  65.05 secs 2 tasks remaining.
Average Wait  99.74 secs 1 tasks remaining.
Average Wait  17.27 secs 0 tasks remaining.
Average Wait 239.61 secs 5 tasks remaining.
Average Wait  75.11 secs 1 tasks remaining.
Average Wait  48.33 secs 0 tasks remaining.
Average Wait  39.31 secs 3 tasks remaining.
Average Wait 376.05 secs 1 tasks remaining.
我们可以看到，平均等待时间为 122.09 秒。 还可以看到平均等待时间有很大的变化，
最小值为 17.27 秒，最大值为 376.05 秒。 你也可能注意到，只有两种情况所有任务都完成。

# 打印速度 每分钟 10 页，再次运行 10 次测试，页面速度更快，我们希望在一小时内完成更多的任务。
>>>for i in range(10):
      simulation(3600,10)

Average Wait   1.29 secs 0 tasks remaining.
Average Wait   7.00 secs 0 tasks remaining.
Average Wait  28.96 secs 1 tasks remaining.
Average Wait  13.55 secs 0 tasks remaining.
Average Wait  12.67 secs 0 tasks remaining.
Average Wait   6.46 secs 0 tasks remaining.
Average Wait  22.33 secs 0 tasks remaining.
Average Wait  12.39 secs 0 tasks remaining.
Average Wait   7.27 secs 0 tasks remaining.
Average Wait  18.17 secs 0 tasks remaining.

```

## 3. 双端队列 deques
      deque（也称为双端队列）是与队列类似的项的有序集合。
      它有两个端部，首部和尾部，并且项在集合中保持不变。
      deque 不同的地方是添加和删除项是非限制性的。
      可以在前面或后面添加新项。
      同样，可以从任一端移除现有项。
      在某种意义上，这种混合线性结构提供了单个数据结构中的栈和队列的所有能力。 
      
      要注意，即使 deque 可以拥有栈和队列的许多特性，
      它不需要由那些数据结构强制的 LIFO 和 FIFO 排序。
      
      这取决于你如何持续添加和删除操作。

![](https://facert.gitbooks.io/python-data-structure-cn/3.%E5%9F%BA%E6%9C%AC%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/3.15.%E4%BB%80%E4%B9%88%E6%98%AFDeque/assets/3.15.%E4%BB%80%E4%B9%88%E6%98%AFDeque.figure1-1.png)
      
      
### Deque 抽象数据类型
      
    deque 抽象数据类型由以下结构和操作定义。
    如上所述，deque 被构造为项的有序集合，其中项从首部或尾部的任一端添加和移除。
    下面给出了 deque 操作。
      Deque()        创建一个空的新 deque。它不需要参数，并返回空的 deque。
      addFront(item) 将一个新项添加到 deque 的首部。它需要 item 参数 并不返回任何内容。
      addRear(item)  将一个新项添加到 deque 的尾部。它需要 item 参数并不返回任何内容。
      removeFront()  从 deque 中删除首项。它不需要参数并返回 item。deque 被修改。
      removeRear()   从 deque 中删除尾项。它不需要参数并返回 item。deque 被修改。
      isEmpty()      测试 deque 是否为空。它不需要参数，并返回布尔值。
      size()         返回 deque 中的项数。它不需要参数，并返回一个整数。  

    假设 d 是已经创建并且当前为空的 deque:
      操作                DQ状态          返回          说明
      d.isEmpty()          []            True          是否为空
      d.addRear(4)         [4]                         尾部插入4
      d.addRear('dog')     ['dog',4]                   尾部插入'dog'
      d.addFront('cat')    ['dog',4,'cat']             前部插入'cat'
      d.addFront(True)     ['dog',4,'cat',True]        前部插入True
      d.size()             ['dog',4,'cat',True]   4    大小
      d.isEmpty()          ['dog',4,'cat',True]   False  是否为空 
      d.addRear(8.4)       [8.4,'dog',4,'cat',True]    尾部插入8.4
      d.removeRear()       ['dog',4,'cat',True]   8.4  尾部删除8.4
      d.removeFront()      ['dog',4,'cat']        True 尾部删除True
      
### python 实现 Deque
      为抽象数据类型 deque 的实现创建一个新类。
      同样，Python 列表将提供一组非常好的方法来构建 deque 的细节。
      我们的实现假定 deque 的尾部在列表中的位置为 0。
      
```python
class Deque:
    # 初始化空列表
    def __init__(self):
        self.items = []
    # 测试为空？
    def isEmpty(self):
        return self.items == []
    # 前端加入 元素，放在右面 O(1)
    def addFront(self, item):
        self.items.append(item)
    # 尾部加入元素， 在开始0位置插入，O(n)
    def addRear(self, item):
        self.items.insert(0,item)
    # 首部删除元素，删除右边的元素 O(n)
    def removeFront(self):
        return self.items.pop()
    # 尾部删除元素，删除位置0上的元素 O(n)
    def removeRear(self):
        return self.items.pop(0) # pop(0)方法必须删除列表的第一个元素。
    # 队列大小
    def size(self):
        return len(self.items)


```

### 双端队列 deques 应用1： 回文检查
      2018102
      回文是一个字符串，读取首尾相同的字符，
      例如，
        radar
        toot
        madam。 
      我们想构造一个算法输入一个字符串，并检查它是否是一个回文。
![](https://facert.gitbooks.io/python-data-structure-cn/3.%E5%9F%BA%E6%9C%AC%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/3.18.%E5%9B%9E%E6%96%87%E6%A3%80%E6%9F%A5/assets/3.18.%E5%9B%9E%E6%96%87%E6%A3%80%E6%9F%A5.figure2.png)
      
      我们可以直接删除并比较首尾字符，只有当它们匹配时才继续。
      如果可以持续匹配首尾字符，我们最终要么用完字符，
      要么留出大小为 1 的deque，取决于原始字符串的长度是偶数还是奇数。
      在任一情况下，字符串都是回文。

```python

from pythonds.basic.deque import Deque

def palchecker(aString):
    # 空DQ
    chardeque = Deque()
    # 字符串创建 双端队列
    for ch in aString:
        chardeque.addRear(ch)
    # 对等
    stillEqual = True

    while chardeque.size() > 1 and stillEqual:
        # 右边元素
        first = chardeque.removeFront()
        # 左边元素
        last = chardeque.removeRear()
        # 左右两端元素应该匹配
        if first != last:
            # 不匹配，不是 回文
            stillEqual = False

    return stillEqual

print(palchecker("lsdkjfskf"))
print(palchecker("radar"))

```
      
## 4. 列表 List
      列表是一个强大但简单的收集机制，为程序员提供了各种各样的操作。
      然而，不是所有的编程语言都包括列表集合。
      在这些情况下，列表的概念必须由程序员实现。
      
      列表是项的集合，其中每个项保持相对于其他项的相对位置。
      更具体地，我们将这种类型的列表称为无序列表。
      我们可以将列表视为具有第一项，第二项，第三项等等。
      我们还可以引用列表的开头（第一个项）或列表的结尾（最后一个项）。
      为了简单起见，我们假设列表不能包含重复项。
      例如，整数 54,26,93,17,77 和 31 的集合可以表示考试分数的简单无序列表。
      请注意，我们将它们用逗号分隔，这是列表结构的常用方式。
      当然，Python 会显示这个列表为 [54,26,93,17,77,31]。
      
### 无序列表抽象数据类型
      无序列表的结构是项的集合，其中每个项保持相对于其他项的相对位置。
      下面给出了一些可能的无序列表操作。

      List()        创建一个新的空列表。它不需要参数，并返回一个空列表。
      add(item)     向列表中添加一个新项。它需要 item 作为参数，并不返回任何内容。
                    假定该 item 不在列表中。
      remove(item)  从列表中删除该项。它需要 item 作为参数并修改列表。假设项存在于列表中。
      search(item)  搜索列表中的项目。它需要 item 作为参数，并返回一个布尔值。
      isEmpty()     检查列表是否为空。它不需要参数，并返回布尔值。
      size()        返回列表中的项数。它不需要参数，并返回一个整数。
      append(item)  将一个新项添加到列表的末尾，使其成为集合中的最后一项。
                    它需要 item 作为参数，并不返回任何内容。假定该项不在列表中。
      index(item)   返回项在列表中的位置。它需要 item 作为参数并返回索引。假定该项在列表中。
      insert(pos, item) 在位置 pos 处向列表中添加一个新项。
                    它需要 item 作为参数并不返回任何内容。
                    假设该项不在列表中，并且有足够的现有项使其有 pos 的位置。
      pop()         删除并返回列表中的最后一个项。假设该列表至少有一个项。
      pop(pos)      删除并返回位置 pos 处的项。
                    它需要 pos 作为参数并返回项。假定该项在列表中。
      
### 无序列表实现：链表
      这些值已被随机放置。如果我们可以在每个项中保持一些明确的信息，
      即下一个项的位置，则每个项的相对位置可以通过简单地从一个项到下一个项的链接来表示。

![](https://facert.gitbooks.io/python-data-structure-cn/3.%E5%9F%BA%E6%9C%AC%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/3.21.%E5%AE%9E%E7%8E%B0%E6%97%A0%E5%BA%8F%E5%88%97%E8%A1%A8%EF%BC%9A%E9%93%BE%E8%A1%A8/assets/3.21.%E5%AE%9E%E7%8E%B0%E6%97%A0%E5%BA%8F%E5%88%97%E8%A1%A8%EF%BC%9A%E9%93%BE%E8%A1%A8.figure2.png)
      
      要注意，必须明确地指定链表的第一项的位置。
      一旦我们知道第一个项在哪里，第一个项目可以告诉我们第二个是什么，等等。
      外部引用通常被称为链表的头。
      类似地，最后一个项需要知道没有下一个项。
      
      
#### Node 节点类(值+指向)
      链表实现的基本构造块是节点。每个节点对象必须至少保存两个信息。
      首先，节点必须包含列表项本身。我们将这个称为节点的 数据字段。
      此外，每个节点必须保存 对 下一个节点的引用。 
      Node 类还包括访问，修改数据和访问下一个引用的常用方法。
```python
class Node:
    def __init__(self,initdata):
        # 数据字段
        self.data = initdata
        # 对 下一个节点的引用 
        self.next = None
        # 引用 None 代表没有下一个节点。
        # 请注意在构造函数中，最初创建的节点 next 被设置为 None。
        # 有时这被称为 接地节点，因此我们使用标准接地符号表示对 None 的引用。
        
    # 访问数据
    def getData(self):
        return self.data
        
    # 访问下一个引用
    def getNext(self):
        return self.next
        
    # 修改数据
    def setData(self,newdata):
        self.data = newdata
        
    # 修改 下一个引用
    def setNext(self,newnext):
        self.next = newnext

# 我们创建一个 Node 对象
>>> temp = Node(93)
>>> temp.getData()
93



```
      
![](https://facert.gitbooks.io/python-data-structure-cn/3.%E5%9F%BA%E6%9C%AC%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/3.21.%E5%AE%9E%E7%8E%B0%E6%97%A0%E5%BA%8F%E5%88%97%E8%A1%A8%EF%BC%9A%E9%93%BE%E8%A1%A8/assets/3.21.%E5%AE%9E%E7%8E%B0%E6%97%A0%E5%BA%8F%E5%88%97%E8%A1%A8%EF%BC%9A%E9%93%BE%E8%A1%A8.figure4.png) 
      
      
      
#### 无序列表 Unordered List 类
      无序列表将从一组节点构建，每个节点通过显式引用链接到下一个节点。
      只要我们知道在哪里找到第一个节点（包含第一个项），
      之后的每个项可以通过连续跟随下一个链接找到。
      考虑到这一点，UnorderedList 类必须保持对第一个节点的引用。
      
```python
class UnorderedList:

    def __init__(self):
        # 记录表头
        self.head = None
        # 特殊引用 None 将再次用于表示链表的头部不引用任何内容。
        
    # 只是检查链表头是否是 None 的引用 ,判断链表是否为空
    # 显示了使用引用 None 来表示链接结构的 end 的优点
    def isEmpty(self):
        return self.head == None
    
    # 添加一个元素
    def add(self,item):
        # 新建一个节点
        temp = Node(item)
        # 新节点指向 原 链表头的指向 
        temp.setNext(self.head)
        # 在更新链表 头
        self.head = temp
        
    # 遍历链表，获取大小
    def size(self):
        # 表头后的第一个节点
        current = self.head
        count = 0
        
        # 非 接地， 未到 链表结尾
        while current != None:
            count = count + 1 # 计数+1
            current = current.getNext() # 迭代，后一个节点
        return count
        
    # 遍历链表，寻找指定元素
    def search(self,item):
        # 表头后的第一个节点
        current = self.head
        found = False # 未找到
        
        # 未到 链表结尾，且未找到
        while current != None and not found:
            # 该节点 数据项 是否为 指定元素
            if current.getData() == item:
                found = True
            # 遍历下一个节点
            else:
                current = current.getNext()
        # 返回 找到与否标志
        return found
    
    # 删除指定元素
    def remove(self,item):
        # 表头后的第一个节点
        current = self.head
        previous = None
        found = False # 寻找指定元素
        
        # 先寻找指定元素
        while not found:
            # 查看指定节点数据项 是否为 指定元素
            if current.getData() == item:
                # 找到了
                found = True
            # 还未找到
            else:
                # 记录当前节点的前一个节点
                previous = current
                # 更新 下一个节点
                current = current.getNext()
                
        # 一开始就找到了,也就是第一个节点就是要找的元素
        if previous == None:
            self.head = current.getNext()
        # 前一个节点的下一个节点 指向 当前节点的 下一个节点
        else:
            previous.setNext(current.getNext())
    
    
# 我们构建一个空的链表。赋值语句
>>> mylist = UnorderedList()

# 添加元素
>>> mylist.add(31)
>>> mylist.add(77)
>>> mylist.add(17)
>>> mylist.add(93)
>>> mylist.add(26)
>>> mylist.add(54)

# 链表大小
>>> mylist.size()
6

# 作为一个例子，试试调用 search 方法来查找 item 17
>>> mylist.search(17)
True

```

     链表的头指代列表的第一项的第一节点。反过来，
     该节点保存对下一个节点（下一个项）的引用，等等。
     重要的是注意链表类本身不包含任何节点对象。
     相反，它只包含对链接结构中第一个节点的单个引用。 

![](https://facert.gitbooks.io/python-data-structure-cn/3.%E5%9F%BA%E6%9C%AC%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/3.21.%E5%AE%9E%E7%8E%B0%E6%97%A0%E5%BA%8F%E5%88%97%E8%A1%A8%EF%BC%9A%E9%93%BE%E8%A1%A8/assets/3.21.%E5%AE%9E%E7%8E%B0%E6%97%A0%E5%BA%8F%E5%88%97%E8%A1%A8%EF%BC%9A%E9%93%BE%E8%A1%A8.figure6.png)
      
      
      由于该链表是无序的，所以新项相对于已经在列表中的其他项的特定位置并不重要。 
      新项可以在任何位置。考虑到这一点，将新项放在最简单的位置是有意义的。
      
      链表结构只为我们提供了一个入口点，即链表的头部。
      所有其他节点只能通过访问第一个节点，然后跟随下一个链接到达。
      这意味着添加新节点的最简单的地方就在链表的头部。 
      
      换句话说，我们将新项作为链表的第一项，现有项将需要链接到这个新项后。
      
      更改新节点的下一个引用以引用旧链表的第一个节点。
      现在，链表的其余部分已经正确地附加到新节点，我们可以修改链表的头以引用新节点。
      这两个步骤不能反，反了之后就找不到原链表了。
![](https://facert.gitbooks.io/python-data-structure-cn/3.%E5%9F%BA%E6%9C%AC%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/3.21.%E5%AE%9E%E7%8E%B0%E6%97%A0%E5%BA%8F%E5%88%97%E8%A1%A8%EF%BC%9A%E9%93%BE%E8%A1%A8/assets/3.21.%E5%AE%9E%E7%8E%B0%E6%97%A0%E5%BA%8F%E5%88%97%E8%A1%A8%EF%BC%9A%E9%93%BE%E8%A1%A8.figure7.png)
      
      
      遍历链表，获取大小
 ![](https://facert.gitbooks.io/python-data-structure-cn/3.%E5%9F%BA%E6%9C%AC%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/3.21.%E5%AE%9E%E7%8E%B0%E6%97%A0%E5%BA%8F%E5%88%97%E8%A1%A8%EF%BC%9A%E9%93%BE%E8%A1%A8/assets/3.21.%E5%AE%9E%E7%8E%B0%E6%97%A0%E5%BA%8F%E5%88%97%E8%A1%A8%EF%BC%9A%E9%93%BE%E8%A1%A8.figure9.png)
      
      
      我们检查存储在当前节点中的项是否是我们希望删除的项。
      如果是，found 设置为 True 。
      如果我们没有找到该项，则 previous 和 current 都必须向前移动一个节点。
      同样，这两个语句的顺序是至关重要的。
      previous 必须先将一个节点移动到 current 的位置。
      此时，才可以移动current。
      这个过程通常被称为“英寸蠕动”，因为 previous 必须赶上 current，然后 current 前进。
![](https://facert.gitbooks.io/python-data-structure-cn/3.%E5%9F%BA%E6%9C%AC%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/3.21.%E5%AE%9E%E7%8E%B0%E6%97%A0%E5%BA%8F%E5%88%97%E8%A1%A8%EF%BC%9A%E9%93%BE%E8%A1%A8/assets/3.21.%E5%AE%9E%E7%8E%B0%E6%97%A0%E5%BA%8F%E5%88%97%E8%A1%A8%EF%BC%9A%E9%93%BE%E8%A1%A8.figure12.png)
      
      一旦 remove 的搜索步骤已经完成，我们需要从链表中删除该节点。 
![](https://facert.gitbooks.io/python-data-structure-cn/3.%E5%9F%BA%E6%9C%AC%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/3.21.%E5%AE%9E%E7%8E%B0%E6%97%A0%E5%BA%8F%E5%88%97%E8%A1%A8%EF%BC%9A%E9%93%BE%E8%A1%A8/assets/3.21.%E5%AE%9E%E7%8E%B0%E6%97%A0%E5%BA%8F%E5%88%97%E8%A1%A8%EF%BC%9A%E9%93%BE%E8%A1%A8.figure13.png)
      
      有一个特殊情况需要解决。 如果要删除的项目恰好是链表中的第一个项，则 current 将引用链接列表中的第一个节点。
      这也意味着 previous 是 None。 我们先前说过，previous 是一个节点，它的下一个节点需要修改。
      在这种情况下，不是 previous ，而是链表的 head 需要改变
![](https://facert.gitbooks.io/python-data-structure-cn/3.%E5%9F%BA%E6%9C%AC%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/3.21.%E5%AE%9E%E7%8E%B0%E6%97%A0%E5%BA%8F%E5%88%97%E8%A1%A8%EF%BC%9A%E9%93%BE%E8%A1%A8/assets/3.21.%E5%AE%9E%E7%8E%B0%E6%97%A0%E5%BA%8F%E5%88%97%E8%A1%A8%EF%BC%9A%E9%93%BE%E8%A1%A8.figure14.png)
      
      
#### 有序列表抽象数据结构 Ordered List

      如果上面所示的整数列表是有序列表（升序），则它可以写为 17,26,31,54,77和93。
      由于 17 是最小项，它占据第一位置。同样，由于 93 是最大的，它占据最后的位置。
      
      排序通常是升序或降序，并且我们假设列表项具有已经定义的有意义的比较运算。
      许多有序列表操作与无序列表的操作相同。

      OrderedList()   创建一个新的空列表。
                      它不需要参数，并返回一个空列表。
      add(item)       向列表中添加一个新项。
                      它需要 item 作为参数，并不返回任何内容。
                      假定该 item 不在列表中。
      remove(item)    从列表中删除该项。
                      它需要 item 作为参数并修改列表。
                      假设项存在于列表中。
      search(item)    搜索列表中的项目。
                      它需要 item 作为参数，并返回一个布尔值。
      isEmpty()       检查列表是否为空。
                      它不需要参数，并返回布尔值。
      size()          返回列表中的项数。
                      它不需要参数，并返回一个整数。
      index(item)     返回项在列表中的位置。
                      它需要 item 作为参数并返回索引。
                      假定该项在列表中。
      pop()           删除并返回列表中的最后一个项。
                      假设该列表至少有一个项。
      pop(pos)        删除并返回位置 pos 处的项。
                      它需要 pos 作为参数并返回项。
                      假定该项在列表中。


```python
class OrderedList:
    def __init__(self):
        # head 的引用为 None 表示为空链表
        self.head = None
        
    # isEmpty 和size 方法可以与无序列表一样实现，因为它们只处理链表中的节点数量，而不考虑实际项值。
        
    # 只是检查链表头是否是 None 的引用 ,判断链表是否为空
    # 显示了使用引用 None 来表示链接结构的 end 的优点
    def isEmpty(self):
        return self.head == None
        
    # 遍历链表，获取大小
    def size(self):
        # 表头后的第一个节点
        current = self.head
        count = 0
        
        # 非 接地， 未到 链表结尾
        while current != None:
            count = count + 1 # 计数+1
            current = current.getNext() # 迭代，后一个节点
        return count
        
    # 同样，remove 方法将正常工作，因为我们仍然需要找到该项，然后删除它。
    # 删除指定元素
    def remove(self,item):
        # 表头后的第一个节点
        current = self.head
        previous = None
        found = False # 寻找指定元素
        
        # 先寻找指定元素
        while not found:
            # 查看指定节点数据项 是否为 指定元素
            if current.getData() == item:
                # 找到了
                found = True
            # 还未找到
            else:
                # 记录当前节点的前一个节点
                previous = current
                # 更新 下一个节点
                current = current.getNext()
                
        # 一开始就找到了,也就是第一个节点就是要找的元素
        if previous == None:
            self.head = current.getNext()
        # 前一个节点的下一个节点 指向 当前节点的 下一个节点
        else:
            previous.setNext(current.getNext())
            
    # search 和 add，将需要一些修改=====================   
            
    '''
    最重要的需要修改的方法是 add。 
    回想一下，对于无序列表，add 方法可以简单地将新节点放置在链表的头部。
    这是最简单的访问点。 不幸的是，这将不再适用于有序列表。
    需要在现有的有序列表中查找新项所属的特定位置。
    假设我们有由 17,26,54,77 和 93 组成的有序列表，并且我们要添加值31 。
    add 方法必须确定新项属于 26 到 54 之间。
    我们知道，当我们迭代完节点（ current 变为 None）
    或 current 节点的值变得大于我们希望添加的项时，我们就找到了该位置。
    在我们的例子中，看到值 54 我们停止迭代。
   
    '''
            
    # 添加一个元素，需要排序放入合适的位置
    def add(self,item):
        # 两个哥俩，一前一后双指针
        current = self.head # 
        previous = None
        # 提前结束标志
        stop = False
        
        # 遍历找到有序链表中的合适位置
        while current != None and not stop:
            if current.getEats() > item:
                # 找到合适位置了
                # current 节点的值变得大于我们希望添加的项时，我们就找到了该位置。
                # 应当停下来
                stop = True
            else:
                # 还未找到，更新两个 哥俩
                previous = current
                current  = current.getNext()
                
        # 新建一个节点
        temp = Node(item)
        if previous == None:
            # 添加的元素最小，需要放在表头
            # 新节点指向 原 链表头的指向 
            temp.setNext(self.head)
            # 更新链表 头
            self.head = temp
        else:
            # 正常的放在 current 之前，previous 节点之后 
            temp.setNext(current)  # current 之前
            previous.setNext(temp) # previous 节点之后
            
        
        
    # 遍历链表，寻找指定元素
    # 在项不在链表中的情况下，我们可以利用 有序结构 来尽快停止搜索。
    def search(self,item):
        # 表头后的第一个节点
        current = self.head
        found = False # 未找到
        
        # 添加另一个布尔变量======用于是否停止寻找==========
        stop = False
        
        # 未到 链表结尾，且未找到,且未停止
        while current != None and not found and not stop:
            # 该节点 数据项 是否为 指定元素
            if current.getData() == item:
                found = True
            # 遍历下一个节点
            else:
                # 如果发现任何节点包含大于我们正在寻找的项的数据，我们将 stop 设置为 True,不要寻找了
                if current.getData() > item:
                    stop = True # 不用找了
                else:
                    current = current.getNext()
        # 返回 找到与否标志
        return found 
'''
你可能还注意到此实现的性能与早前针对 Python 列表给出的实际性能不同。
这表明链表不是 Python 列表的实现方式。
Python 列表的实际实现基于数组的概念。
'''
```
      
      
有序表中添加新项:

![](https://facert.gitbooks.io/python-data-structure-cn/3.%E5%9F%BA%E6%9C%AC%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/3.23.%E5%AE%9E%E7%8E%B0%E6%9C%89%E5%BA%8F%E5%88%97%E8%A1%A8/assets/3.23.%E5%AE%9E%E7%8E%B0%E6%9C%89%E5%BA%8F%E5%88%97%E8%A1%A8.figure17.png)
      
#### 总结
      线性 数据结构 以 有序的方式保存它们的数据。
      栈是维持 LIFO，后进先出，排序的简单数据结构。
      栈的基本操作是 push，pop和 isEmpty。
      队列是维护 FIFO（先进先出）排序的简单数据结构。
      队列的基本操作是 enqueue，dequeue 和 isEmpty。
      前缀，中缀 和 后缀 都是写表达式的方法。
      栈 对于设计计算解析表达式算法非常有用。
      栈可以提供 反转特性。
      队列可以帮助 构建定时仿真。
      模拟使用 随机数生成器 来创建真实情况，并帮助我们回答“假设”类型的问题。
      Deques 是允许类似 栈 和 队列 的混合行为的 数据结构。
      Deque  的基本操作是 addFront，addRear，removeFront，removeRear 和 isEmpty。
      列表是 项 的集合，其中每个项目保存相对位置。
      链表 实现 保持逻辑顺序，而不需要物理存储要求。
      修改 链表头 是一种特殊情况。

      
# 二、递归算法思想---分而治之----减而治之
      要理解可能难以解决的复杂问题有一个简单的递归解决方案。
      学习如何递归地写出程序。
      理解和应用递归的三个定律。
      将递归理解为一种迭代形式。
      实现问题的递归公式化。
      了解计算机系统如何实现递归。     
      
      递归是一种解决问题的方法，
      将问题分解为更小的子问题，
      直到得到一个足够小的问题可以被很简单的解决。
      通常递归涉及函数调用自身。
      递归允许我们编写优雅的解决方案，解决可能很难编程的问题。

## 计算整数列表和
循环计算
```python
def listsum(numList):
    theSum = 0
    # for循环变量 列表中的每个元素
    for i in numList:
        theSum = theSum + i
    return theSum

print(listsum([1,3,5,7,9]))


```


递归实现
```python
def listsum(numList):
   # 问题规模最小时的情况
   if len(numList) == 1:
        return numList[0]
   # 大问题分解成多个小问题
   else:
        # 函数调用自己，递归调用
        return numList[0] + listsum(numList[1:])

print(listsum([1,3,5,7,9]))
```
![](https://facert.gitbooks.io/python-data-structure-cn/4.%E9%80%92%E5%BD%92/4.3.%E8%AE%A1%E7%AE%97%E6%95%B4%E6%95%B0%E5%88%97%E8%A1%A8%E5%92%8C/assets/4.3.%E8%AE%A1%E7%AE%97%E6%95%B4%E6%95%B0%E5%88%97%E8%A1%A8%E5%92%8C.figure2.png)
      
      
      
