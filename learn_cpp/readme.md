# 学习C++

## 鱼C工作室 C++快速入门
[鱼C工作室 C++快速入门](http://blog.fishc.com/category/cpp/page/5)

[C++ Primer 5 代码](https://github.com/Ewenwan/Cpp-Primer)


#    C++  泛型技术  泛化技术  增加不确定性  通用性  灵活性

> 所谓泛型技术，说白了就是试图使用不变的代码来实现可变的算法

> 比如：模板技术，RTTI技术，虚函数技术

> 要么是试图做到在编译时决议，要么试图做到运行时决议。


## 【【A】】 RTTI技术
    RTTI(Run-Time Type Identification)是面向对象程序设计中一种重要的技术。
    
现行的C++标准对RTTI已经有了明确的支持。不过在某些情况下出于特殊的开发需要，

我们需要自己编码来实现。本文介绍了一些关于RTTI的基础知识及其原理和实现。

    RTTI需求：
　　和很多其他语言一样，C++是一种静态类型语言。其数据类型是在编译期就确定的，
  
不能在运行时更改。然而由于面向对象程序设计中多态性的要求，C++中的指针或引用

(Reference)本身的类型，可能与它实际代表(指向或引用)的类型并不一致。有时我们需

要将一个多态指针转换为其实际指向对象的类型，就需要知道运行时的类型信息，

这就产生了运行时类型识别的要求。


      C++对RTTI的支持：
    
      C++提供了两个关键字typeid（指示类型） 和dynamic_cast（类型强转）和一个type_info类来支持RTTI

#############################################################
###【1】dynamic_cast操作符：     运行时强制类型转换
它允许在运行时刻进行类型转换，
从而使程序能够在一个类层次结构安全地转换类型。
dynamic_cast提供了两种转换方式，
把基类指针转换成派生类指针，
或者把指向基类的左值转换成派生类的引用。
见下例讲述：

    void company::payroll(employee *pe) {//指针

      //对指针转换失败，dynamic_cast返回NULL

      if(programmer *pm=dynamic_cast(pe)){  //基类 employee >>> 派生类 programmer

        pm->bonus(); 

       }

    }
    void company::payroll(employee &re) {//引用  变量别名

    try{

    //对引用转换失败的话，则会以抛出异常来报告错误

      programmer &rm = dynamic_cast(re);

      rm->bonus();
    }

    catch(std::bad_cast){
      }
    }
这里bonus是programmer的成员函数，基类employee不具备这个特性。

所以我们必须使用安全的由基类到派生类类型转换，识别出programmer指针。



    int a=1;int *p=&a;//指针是变量的地址    *p  定义时  和 在函数参数中时  是 表示指针变量   其他表示取值

    int a=1;int &b=a;//引用 是 变量别名     &放在左边 以及在 函数参数中 是引用   方在右边是 取地址

上面定义了一个整形变量和一个指针变量p，该指针变量指向a的存储单元，

即p的值是a存储单元的地址。

而下面2句定义了一个整形变量a和这个整形a的引用b，

事实上a和b是同一个东西，在内存占有同一个存储单元。

区别：
【1】可以有const指针，但是没有const引用；

【2】指针可以有多级，但是引用只能是一级（int **p；合法 而 int &&a是不合法的；

【3】指针的值可以为空，但是引用的值不能为NULL，并且引用在定义的时候必须初始化；

【4】指针的值在初始化后可以改变，即指向其它的存储单元，而引用在进行初始化后就不会再改变了；

【5】"sizeof引用"得到的是所指向的变量(对象)的大小，而"sizeof指针"得到的是指针本身的大小；

【6】指针和引用的自增(++)运算意义不一样；

【7】引用作为函数的参数进行传递，传递的是实参本身，不是实参的一个拷贝；

【8】 用指针传递参数，可实现对实参进行改变的目的，是因为传递过来的是实参的地址，但是指针不会改变。


    #include<iostream>
    using namespace std;

    void test(int *&p)//这里是 指针p的引用  ；如果是 *p 指针 p修改不了 可以修改p指向的内容
    {
      int a=1;
      p=&a;//可以修改p   这里的& 是取地址
      cout<<p<<" "<<*p<<endl;//这里的*是取值
    }

    int main(void)
    {
        int *p=NULL;//这里的 *是 指针变量定义
        test(p);
        if(p!=NULL)
        cout<<"指针p不为NULL"<<endl;
        system("pause");
        return 0;
    }



### 【2】typeid操作符：它指出指针或引用指向的对象的实际派生类型。

例如：

    employee* pe=new manager;

    typeid(*pe) == typeid(manager) //等于true

    typeid的返回是type_info类型。

    class type_info {

    private:

       type_info(const type_info&);

       type_info& operator=( const type_info& );

    public:

       virtual ~type_info();

       int operator==( const type_info& ) const;

       int operator!=( const type_info& ) const;

       const char* name() const;
    };




##############################
## 【【B】】模板

### 【1】函数模板

#### 函数的重载。例如:
    int add(int a, int b)  
    {  
        return a + b;  
    }  
    double add(double a, double b)  
    {  
        return a + b;  
    }  
    char add(char a, char b)  
    {  
        return a + b;  
    }  
这些函数几乎相同，每个函数的函数体是相同的，功能也是相同的，
它们之间唯一的不同在于形参的类型和函数返回值的类型。

C++有模板(template)机制，可以使用函数模板解决上述存在的问题。
函数模板(function template)是一个独立于类型的函数，
可作为一种模式，产生函数的特定类型版本。

    template<模板形参表>返回值类型 函数名(形式参数列表)  
    {  
        函数体  
    }  

模板形参表(template parameter list)是用一对尖括号<>括起来的
一个或多个模板形参的列表，不允许为空，形参之间以逗号分隔。

    第一种形式如下所示:  
         <typename 类型参数名1,typename 类型参数名2，..>

    第二种形式如下所示:  
         <class 类型参数名1,class 类型参数名2，...> 

在函数模板形参表中，typename和class具有相同含义，可以互换使用，

或者两个关键字都可以在同一模板形参表中使用。

不过由于C++中class关键字往往容易与类联系在一起，

所以使用关键字typename比使用class更直观，

typename可以更加直观的反映出后面的名字是一个类型名。

模板定义的后面是函数定义，在函数定义中，可以使用模板形参表中的类型参数。

例如:
    template<typename T>T add(T a, T b)  
    {  
        return a + b;  
    }  

函数模板定义语法的含义是一个通用型函数，

这个函数类型和形参类型没有具体的指定，而是一个类型记号表示

，类型记号由编译器根据所用的函数而确定，这种通用型函数成为函数模板。


    #include<iostream>  

    using namespace std;  

    template<typename T>T add(T a, T b)//函数模板
    {  
        return a + b;  
    }  

    int main()  
    {  
        std::cout << "int_add    = "    << add(10,20)<< std::endl;  
        std::cout << "double_add = "    << add(10.2, 20.5) << std::endl;  
        std::cout << "char_add   = "    << add(10, 20) << std::endl;  
        std::system("pause");  
        return 0;  
    }


### 【2】类模板

类似于函数模板的做法，类模板对数据成员的

数据类型和成员函数的参数类型进行泛化。

如下是类模板的一个基本定义形式，

关键字template说明类型T1~Tn是模本类型， typename 或 class关键字 

成员函数可在类模板的声明中定义。

    template<class T1,class T2, ... ,class Tn> class 类名  
    {  
        //数据成员声明或定义;  
    };  
    template<class T1, class T2, ....., class Tn> 返回值 类名<T1,T2, ....., Tn>::成员函数1  
    {  
        //函数定义  
    }  
    template<class T1, class T2, ....., class Tn> 返回值 类名<T1, T2, ....., Tn>::成员函数2  
    {  
        //函数定义  

    }  

不同于非模板代码的组织方式，函数模板和类模板的声明和定义代码，

一般都编写在.h头文件中，以免由于为具现而提示编译链接错误。

下面给出一个类模板表示平面上点的示例:

    template<class T> //【0】类模板定义 

    class Point       //【1】Point不是类名是模板名  

    {  

    public:  

    Point::x(0), y(0) {} //【2】默认构造函数  初始化为0 
    
    Point(const T a, const T b) :(x)(a), y(b) {}//【3】带参数的构造函数    a赋值给x b赋值给y 
    
    void Set(const T a, const T b);  
    
    void Display();  
    
    private:  

        T x;  

        T y;  
    }; 


## 【【C】】虚函数技术

C++中的虚函数的作用主要是实现了多态的机制。

关于多态，简而言之就是用父类型别的指针指向其子类的实例

，然后通过父类的指针调用实际子类的成员函数。

这种技术可以让父类的指针有“多种形态”.


### 虚函数表
 
对C++ 了解的人都应该知道虚函数（Virtual Function）

是通过一张虚函数表（Virtual Table）来实现的。简称为V-Table。

这个表中，主是要一个类的虚函数的地址表，这张表解决了继承、覆盖的问题，

保证其容真实反应实际的函数。这样，在有虚函数的类的实例中这个表被分配在了

这个实例的内存中，所以，当我们用父类的指针来操作一个子类的时候，

这张虚函数表就显得由为重要了，它就像一个地图一样，指明了实际所应该调用的函数。


    class Base {
         public:
                virtual void f() { cout << "Base::f" << endl; }
                virtual void g() { cout << "Base::g" << endl; }
                virtual void h() { cout << "Base::h" << endl; }

    };

我们可以通过Base的实例来得到虚函数表。 下面是实际例程：
 
           typedef void(*Fun)(void);//函数指针  Fun
 
            Base b;//类 
 
            Fun pFun = NULL;
 
            cout << "虚函数表地址：" << (int*)(&b) << endl;//  &b 取地址 (int*) 强制转换成int类型的指针

            cout << "虚函数表 — 第一个函数地址：" << (int*)*(int*)(&b) << endl;
            // (int*)(&b) 虚函数表地址  *(int*)(&b) 取虚函数表地址 内的内容 为 虚函数地址  (int*) 强制转换成int类型的指针

            pFun = (Fun)*((int*)*(int*)(&b));//得到第一个函数 *((int*)*(int*)(&b))
            pFun();
 
实际运行经果如下：
 
虚函数表地址：0012FED4
虚函数表 — 第一个函数地址：0044F148
Base::f

            (Fun)*((int*)*(int*)(&b)+0);  // Base::f()
            
            (Fun)*((int*)*(int*)(&b)+1);  // Base::g()
            
            (Fun)*((int*)*(int*)(&b)+2);  // Base::h()
            

|Base::f()|Base::g()|Base::h()|.|

#### 【1】一般继承（无虚函数覆盖,子类中定义的函数名与父类中的不同）

我们可以看到下面几点：

1）虚函数按照其声明顺序放于表中。

2）父类的虚函数在子类的虚函数前面。

    |Base::f()|Base::g()|Base::h()|Derive::f1()|Derive::g1()|Derive::h1()|.|


#### 【2】一般继承（有虚函数覆盖）
如果子类中有虚函数重载了父类的虚函数   f()

1）覆盖的f()函数被放到了虚表中原来父类虚函数的位置。

2）没有被覆盖的函数依旧。

    |Derive::f1()|Base::g()|Base::h()|Derive::g1()|Derive::h1()|.|

这样，我们就可以看到对于下面这样的程序，
 
            Base *b = new Derive();
 
            b->f();
 
由b所指的内存中的虚函数表的f()的位置已经被Derive::f()函数地址所取代，

于是在实际调用发生时，是Derive::f()被调用了。这就实现了多态。


#### 【3】多重继承（无虚函数覆盖）
 Derive 继承 于 Base1 Base2 Base3

     |Base1::f()|Base1::g()|Base1::h()|Derive::f1()|Derive::g1()|Derive::h1()|.|
     
     |Base2::f()|Base2::g()|Base2::h()|.|
     
     |Base3::f()|Base3::g()|Base3::h()|.|
     

我们可以看到：

1）  每个父类都有自己的虚表。

2）  子类的成员函数被放到了第一个父类的表中。（所谓的第一个父类是按照声明顺序来判断的）


这样做就是为了解决不同的父类类型的指针指向同一个子类实例，而能够调用到实际的函数。


#### 【4】多重继承（有虚函数覆盖）
 Derive 继承 于 Base1 Base2 Base3   且有相同函数 f()

     |Derive::f()|Base1::g()|Base1::h()|Derive::g1()|Derive::h1()|.|

     |Derive::f()|Base2::g()|Base2::h()|.|

     |Derive::f()|Base3::g()|Base3::h()|.|
 
 三个父类虚函数表中的f()的位置被替换成了子类的函数指针。
 
 这样，我们就可以任一静态类型的父类来指向子类，并调用子类的f()了。
 
 如：

            Derive d;
            Base1 *b1 = &d;
            Base2 *b2 = &d;
            Base3 *b3 = &d;
            b1->f(); //Derive::f()
            b2->f(); //Derive::f()
            b3->f(); //Derive::f()
 
            b1->g(); //Base1::g()
            b2->g(); //Base2::g()
            b3->g(); //Base3::g()



#### 【5】安全性
##### 一、通过父类型的指针访问子类自己的虚函数  会出错
          Base1 *b1 = new Derive();
            b1->f1();  //编译出错   f1() 为子类自己的虚函数
任何妄图使用父类指针想调用子类中的未覆盖父类的成员函数的行为都会被编译器视为非法。


##### 二、访问non-public (private 或者 protected)的虚函数

如果父类的虚函数是private或是protected的，但这些非public的虚函数同样会存在于虚函数表中，

所以，我们同样可以使用访问虚函数表的方式来访问这些non-public的虚函数，这是很容易做到的。

    class Base {
        private:
                virtual void f() { cout << "Base::f" << endl; } 
    };


    class Derive : public Base{//继承 于 Base父类
    };


    typedef void(*Fun)(void);//函数指针


    void main() {
        Derive d;
        Fun  pFun = (Fun)*((int*)*(int*)(&d)+0);//调用父类的私有虚函数
        pFun();
    }


下面是一个关于多重继承的虚函数表访问的例程：
[多重继承的虚函数表访问的例程](class_Virtual_Table.cpp)
