[nowcoder刷题笔记](https://blog.csdn.net/fk1174/article/details/52825826)

[LeetCode刷题笔记](https://blog.csdn.net/fk1174/article/details/52744844)

[跟我一起复习C++](https://blog.csdn.net/fk1174/article/details/51841025)

[Leetcode常用五大算法思想](https://blog.csdn.net/x_r_su/article/details/52461557)

[清华操作系统 github](http://github.com/oscourse-tsinghua)

# C++ primer5 语言学习记录

# 复合类型
## 引用 &   左值引用lvalue reference  别名; int val; &refval = val; 右值引用 rvalue reference 

	int val = 1024;//整形变量
	int &refVal = val;// 整形引用 refVal 指向 val ，是val的另一个名字，引用必须被初始化，引用不是对象，只是为所存在的对象起的一个别名。
	refVal = 2;       // 把2 赋值给refVal 也就是 赋值给了 val
	int i = refVal;   // 相当于 i = val; 
	int &refVal2 = 10;// 错误，非常量引用只能绑定(bind)在对象向,不能与字面值或某个表达式的计算结果绑定在一起, 且引用的类型 必须和 对象的类型一致
	const int &rci = 10;// 常量引用可以绑定到 字面值 非常量 一般表达式
	double dval = 3.14;// 浮点数
	int &refVal3 = dval; // 错误，引用的类型 和 对象 必须一致

## 指针 pointer * 指向 point to 另外一个对象（其存储地址）
    int ival = 42;  // 整数
    int *p = &ival; // 指针定义 p存放 ival对象存放的地址，也即是 p 指向 变量 ival的指针   &ival 为取的 ival变量的 存储地址
    double dval = 3.14; // 浮点数
    double *pd = &dval; // double 类型 指针
    double *pd2 = pd;   // pd存放 的是 dval存放的地址

    int *pi = pd;     // 错误， 指针pi 的类型 和 右边指针对象 类型 不匹配
    pi = &dval;   // 错误， 视图把 double 类型对象的地址 给 int类型的指针 错误  左右两边类型 必须匹配
    
> 利用指针访问对象 取地址内存储的值 解引用符 来访问向

	int ival = 42; //整形 变量
	int *p = &ival;//指针变量定义初始化， p 存放着 变量ival 在内存中的地址
	std::cout << *p;// 表达式里 *p 为 解引用 取的p存放的地址 指向的值
	int &ref_i = ival; // 引用声明定义， ref_i 是一个引用
	int *p; //指针声明定义，p是一个指针
	p = &ival;// 表达式 p为指针（地址），&val 为取的 val 地址
	*p = ival;   //表达式  *p 相当于 ival *是一个解引用
	int &ref_i2 = *p;// &ref_i2 为引用定义 *p 相当于 ival， *是一个解引用
    
    
> 空指针

        int *p1 = nullptr;// 等价于 int *p1 = 0; 空指针  p1 不指向 任何 对象
        int *p2 = 0; // 空指针     等价于 int *p1 = 0;
        int *p3 = NULL;// 空指针   等价于 int *p1 = 0;
        int zero = 0;
        int *p4 = zero;// 错误，不能把 int 变量直接赋值 给指针

        int i = 42;
        int *pi1 = 0; // pi1 被初始化为空指针，但没有指向 任何对象
        int *pi2 = &i;// pi2 被初始化，存有 i 的地址
        int *pi3;// 定义 未初始化
        pi3 = pi2;// pi3 和 pi2指向同一个 对象 i
        pi2 = 0; // 现在 pi2 被赋值为 空指针 不指向任何对象  指针被改变， 指向的对象不变
        pi2 = &i;// 现在 pi2 又指向 i
        *pi2 = 0;// 指针pi2 没变 , *pi2 被改变 即pi2指向的对象 i 发生了变化
    

> 使用指针作为条件 为空指针时，逻辑值为 False，其他指向一个对象的指针(非0指针) 逻辑值 均为 true

> 相等 == 操作符  不等 != 操作符 

> void* 类型的指针  可一指向 任意类型 的 地址 ， 可一存放任意类型的 地址，

> 用作函数参数，函数体内使用时需要，转化成实际传入类型的指针

    double obj = 3.14, *pd = &obj; // double 类型 的变量 double类型的指针
    void *pv = &obj; // obj 可以是任意类型的对象
    pv = pd; // pv 可一存放任意类型的指针（地址）
    double *pd = (double*)(pv);// void* 类型的指针 强制转化成  double* 类型的指针
    

> 定义多个变量

    int i = 1024， *p = &i, &r = i;//i是整形变量 p是一个整形指针 r是一个整形引用
    int* p1, p2;// * 仅仅修饰 p1 ，即p1是 指向整形的指针 p2是整形变量
    int *p1, *p2;// p1 和 p2 都是指向 整形的指针
    

> 指向指针的指针

    int ival = 1024;
    int *pi = &ival; //指向整形变量的指针
    int **ppi = &pi; //指向整形指针的指针  ppi ---> pi ------> ival
    std::cout << ival << "\n"// 直接输出 变量值
              << *pi  << "\n"// 1次解引用 得到变量值
              << **ppi<< "\n";//2次解引用 的到变量值


> 指向指针的 引用 指针对象的别名  引用不是对象 不存在 指向引用的指针

	int i = 42;//整形对象
	int *p;//指向整形类型的指针
	int *&r_p = p;//引用r_p的类型为 整形的指针引用int*&，r_p 是指针p的一个别名 
	 //从右向左 离变量最近的符号为 & 即为 引用，* 引用的为 指针类型
	r_p = &i;// 相当于 p = &i p 指向 i
	*r_p = 0;// 相当于 *p = 0 即 i =0 改变了指针指向对象的值  这里 *p *解引用指针的类型其实相当于 原变量的别名 引用


## const 限定符
> 修饰变量后，可以防止变量被修改

	const int bufSize = 512;//初始化常量 一旦创建后就不能被修改
	bufSize = 1024;// 错误，常量不能被赋值
	const int i = get_size();// 一个函数赋值 运行时初始化
	const int j = 42;//编译时初始化
	const int k;//错误，常量定义式必须初始化
	double dvel = 3.14;//  也可以由其他类型变量 强制转换成 常量
	const int ci = dvel;// 由double类型变量 强制转换成 整形常量 3
	extern const int bufSize = 1024;//定义了一个变量，想在其他文件也使用 bufSize 必须在定义之前 加extern
	extern const int bufSize;// 另一个文件中 声明 bufSize 后 就可以使用了
        
> 绑定到常量的引用 const 的引用 即对常量的引用 reference to const 常量 的 别名 不能修改 不存在常量引用 &const 引用不是对象

        const int c_i = 1024;   // 常整数
        const int &r_c_i = c_i; // 常整数 c_i 的 引用（别名）
        r_c_i = 42;// 错误r_c_i 是常量引用 不能被修改
        int &r_c_i2 = c_i;//错误 常整数 不能赋值给 int变量 左右两边类型必须一样

> 允许将一个常量引用绑定到 非常量对象、字面值，甚至是个 一般表达式

        int i = 52;
        const int &r1 = i; // 允许将 常量引用 const int & 绑定到 int变量上
        const int &r2 = 42;// 绑定到 字面值上
        const int &r3 = r1 * 2;// 绑定到一个 表达式上
        int &r4 = r1 * 2;// 错误，r4是非常量 引用，只能绑定到 其对应类型的对象上

        double dval = 3.14;//浮点数
        const int &ri = dval;//常量引用 绑定到 非常量上 
        //相当于 先把 非常量转化成常量 强制类型转换 常量引用实际上绑定了一个临时变量
        const int temp = dval;//

        int i = 42;// int 变量
        int &r1 = i;// 整数变量引用 r1为 i 的别名
        const int &r2 = i;//常量 引用 r2 绑定到 变量 i上
        r1 = 0;// 相当于 i =0
        r2 = 0;// 错误 r2 时常量引用 不允许改变

> 指向常量的指针  const int *   指针指向的值不能变  也就是 *p 不能被赋值 不能改变


            const double pi = 3.14;//双精度 浮点型 常量
            double *ptr_d = &pi;// 错误，浮点型变量指针 不能绑定一个 常量的存储地址
            const double *ptr_d_c = &pi;// 双精度常量 针 ptr_d_c  指向一个 双精度常量
            *ptr_d_c = 42;// 不能给 pi 赋值 指向常量的指针的解引用相当于 绑定的常量 ，因此不能赋值
            doubel dvel = 3.14;//双精度变量
            ptr_d_c = &dvel;//允许 常量指针ptr_d_c 指向一个变量dvel 但是不能通过 常量指针ptr_d_c 修改变量dvel


> 常量指针 *const 指针本身不能改变 也就是指向不能改变  p不能改变 但是其指向的对象 无影响

        int errNumber = 0;//
        int *const conpErr = &errNumber;// * 可变指针  *const 常量指针不可变 指向整形的 常量指针，conpErr 一直指向 errNumber
        *conpErr = 3;//相当于 errNumber = 3
        const double pi = 3.14;//
        const double *const cd_cp = &pi;//指向 常量的常量指针，即 指针本身cd_cp不能变， 其指向的值 *cd_cp也不能变

> 常量表达式 编译时就能确定的量/式子 constexpr int ce = 20;

        const int *p = nullptr;// 指向整形常量 的指针
        constexpr int *p = nullptr;//指向整形变量的 常量指针   constexpr 声明中出现 指针 仅仅说明 指针为常量指针
        int *const p =nullptr;//指向 整形变量的 常量指针
        const int *const p = nullptr;// 指向 整形常量 的常量指针
        constexpr const int *p = nullptr;// 指向 整形常量 的常量指针

        constexpr int ci = 42; // ci 是整形常量
        int j = 0;
        constexpr int *pci = &j; // 指向整形的 常量指针

## 处理类型

### 类型别名  type alias

	typedef double wages;   // wages 是double类型的 同义词
	typedef wages base, *p; // base 也是double类型的 同义词。 p是double * 的同义词
	wages d_money = 1.00;//等有价于 double d_money = 1.00
	p p_dmoney =   &d_money;//等价于 double *p_dmoney =   &d_money;
	cout << p_dmoney << endl; 
	 // 别名声明 alias declaration
	using SI = Sales_Item; // SI 是 Sales_Item 的 同义词
	SI item;//等价于 Sales_Item item;
	 // 指针、常量const 类别别名
	typedef char *pstring;// pstring等价于 char *  指向char 的指针（是指针）
	const pstring cstr = 0;// cstr是指向 char 的 常量指针 ！！！！不是指向常量字符的 指针 不能直接替换 const修饰的主语是指针
	const pstring *ps;     // ps是一个指针 它指向的对象 是 指向char的常量指针

### auto 类型说明符  让 编译器根据右式 类型 自动推算左式的类型  且用表达式的值 初始化变量

        auto item = val1 +val2;//item 初始化为 val1 和 val2相加的结果 类型 相同
        // 一条语句定义多个变量时，各变量类型必须一致
        auto i=0, *p = &i;//正确 i是整数， p是指向整形的指针
        auto sz = 0, pi = 3.4;// 错误 sz 和 pi 类型不一致

        // 引用 指针 常量 与 auto
        int i = 0, &r = i;//r是i的别名 int类型
        auto a = r;// a 是一个整形数

        // auto 会忽略掉 顶层const
        const int ci = i, &cir = ci;// 常整数
        auto b = ci;  // b是一个整数，ci的顶层 const(最外层修饰 为顶层)特性被忽略
        auto c = cir; // c是一个整数，ci的顶层 const特性被忽略
        auto d = &i;  // d是一个指向整形的指针
        auto e = &ci; // e是一个指向整形常量的指针 const 外又被 取地址符号修饰，所以这里的 const是 底层const 不被忽略

        // 如果希望 auto 推断出的类型是 一个顶层 const，需要在其前面 明确指出
        const auto f = ci; // ci的推演类型是 int ，f是 const int

        // 将引用设置为 auto 还按之前的初始化规则  保留 顶层 const
        auto &g = ci; // g 是一个 整形常量的 引用 （别名）
        auto &h = 42; // 错误，非常量 引用 不能绑定 到 字面值
        const auto &j = 42; // 正确， 常量引用可以绑定到 字面值

        // 将 指针设置为 auto， 也按之前的初始化规则 保留顶层 const
        auto *k = &ci; // k为指向 整形常量的 指针
        auto *l = 0;   // l为空指针
        const auto *m = &ci; // m 为 指向整形常量的 常量指针

        int i = 1024;
        const int c_i = i;
        auto b = c_i; // b是一个 整数 ,c_i的 顶层 const被忽略
        auto e = &c_i;// e 是一个 指向 整形常量的引用  这里的const是底层const 不被忽略
        auto k = c_i, &ll = i;// k 是整数， ll 是一个整数引用
        auto k = c_i, &o = c_i;// 错误，k 是整数变量 o是一个整数常量引用 类型不一致
        auto &m =c_i, *p = &c_i;//正确 m是整数常量引用，p是指向整数常量的指针
        auto n = &c_i, *p = &c_i;// 正确 n是整数常量 引用(底层const，不被忽略) p是指向整数常量的指针
        
  
  ### decltype 类型指示符  用表达式推断类型 但是不用表达式的值初始化变量   
  
        decltype(f()) sum = x; // sum 的类型为 函数 f() 的返回值类型 初始化为 x 就像 int sum = x; 一样
        const int ci = 0, &cj = ci;// ci 整形常量  cj 整形常量的引用
        decltype(ci) x = 0; // x的类型 同ci 是 整形常量 const int 不忽略 顶层 const
        decltype(cj) y = x; // y的类型 同cj 是 整形常量的引用 const int &  y绑定到x上
        decltype(cj) z;     // 错误 z是一个 引用 ，必须初始化

        // decltype和引用 指针
        int i =42, j=12, *p = &i, &r = i;
        decltype(r) a = j;// a的类型和r的类型一致，为整数的引用 int& a绑定到j上
        decltype(r + 0) b;//正确 加法的结果为 整形 int 因此 b为整形， 这里只定义 没有初始化
        decltype(*p) c; // 错误 其实*p 解引用指针 相当于i的别名 也就是引用 ，所有这里 c的类型为 整数引用 int &，是个引用，必须初始化

        // decltype 的表达式如果 加上括号，得到的结果将是引用
        decltype(i) e; // e 是一个未初始化的 整形变量
        decltype((i)) d = e; // d是一个 整数的引用 绑定到 整形变量 e上  双层引用括号 的结果 永远都是 

        // 赋值表达式 也会产生 引用 引用的类型就是 等式左边变量的类型 如果 i是int i = x的类型是 int&
 
 # 标准库 std
 ## 字符串类 string 类  #include <string> 存储一个可变长度的 字符串          使用内置数组类型实现
 
 ### 范围for  访问所有元素
 
	string str("some string");
	for (auto c : str)// auto自动推断类型
	cout << c << endl; 
	// 范围for 引用 改变 内容
	string s("Hello World!!!");
	for (auto &c : s)// c是 字符串中每个元素的一个别名
	c = toupper(c);//变成大写
	cout << s << endl;
     
 ### 下标运算符(索引)[] 和 迭代器 访问单个元素
 > string的下标 类型为 string::size_type 无符号数 可用 decltype(s.size())获取 s[0] 是第一个字符 s[s.size()-1]是最后一个字符
 
		// 第一个字符改为大写
		string s("some string");
		if(!s.empty())
			s[0] = toupper(s[0]);//第一个字符改为大写  在 cctype头文件中
		// 第一个单词改为大写
		for(decltype(s.size()) index = 0;
		    index != s.size() && !isspace(s[index]; ++index))
			s[index] = toupper(s[index]);
	 
## 向量 模板  容器container  vector 模板  #include <vector> 存储一个可变长度的 对象 集合 使用内置数组类型实现
> 因为 vector 可以存放任意类型 所以事先需要知道 存放的对象是什么类型  vector<int> ivec; vector<string>; vector<vector<string> >;
    
	// 初始化方式
	vector<int> ivec(10,-1);// 直接初始化 10个元素 全为 -1
	vector<int> ivec2 = ivec;//拷贝初始化
	vector<int> ivec3{10};//一个元素 10 
	vector<int> ivec3{10，1};//两个元素 10  和 1
	vector<string> svec{"a","an","the"};//列表初始化 直接方式
	vector<string> svec2 = {"a","an","the"};//列表初始化 拷贝方式
	
	// 默认初始化 
	vector<int> ivec(10);    // 10个元素，每个值都是0 
	vector<string> svec(10); // 10个元素，每个值都是空 string 对象
	vector<string> svec2{10};// 10个元素，每个值都是空 string 对象
	vector<string> svec3{10, "hi"};// 10个 "hi"元素
	vector<string> svec3(10, "hi");// 10个 "hi"元素
	
	// 使用 .push_back() 添加元素
	vector<int> ivec2; //空vec对象
	for(int i = 0; i != 100; ++i)
	ivec2.push_back(i);// 一次把整数值 放到 ivec2尾部 结束后 ivec2有100个元素 0~99
	
	// 实时添加 string 元素
	string word;
	vector<string> text;//空对象
	while (cin >> word) 
	text.push_back(word);// 把word添加到 text 后面
	
	//使用范围for  + 引用 访问 并改变vector元素
	vector<int> iv{1,2,3,4,5,6,7,8,9};// 列表直接初始化
	for (auto &i : v)// 对于v中每个 元素的 引用 需要改变其值
	i *= i;      // 变成原来值 的 平方
	for (auto i : v) // 仅读取其中的变量
	cout << i << " ";
	cout << endl;
	
	// vector 对象大小 类型为size_type
	vector<int>::size_type se = iv.size();
	
	// 使用索引[] 访问 计算vector对象元素索引   统计各个分数段上 出现的 成绩个数
	// 索引不能添加元素
	vector<unsigned> scores(11,0);//11个分数段， 0~9，10~19，...,90~99，100 计数值全部初始化为0
	unsigned grade;
	while (cin >> grade){
	if(grade <= 100) ++scores[grade/10];
	}    
	
	// cin 读入一组词 改成大写 存入 vector中  #include <cctype> 使用toupper()
	vector<string> sv;
	string word1 = "qwe";
	cout << word1 << endl; 
	while(cin >> word1){
	        for (auto &c : word1) c = toupper(c);
		sv.push_back(word1); 	
		cout << word1 << endl; vector  
	}

## 迭代器 访问容器中的 元素 auto b = v.begin(), e = v.end(); b表示v的第一个元素 e表示v尾元素 的下一个位置  类似 指针

	// 修改 字符串 第一个元素为大小字符
	string s("some string");
	if (s.begin() != s.end()){//确保 s非空
	  auto it = s.begin();// it 指向 s的第一个字符 类似指针 的作用
	  *it = toupper(*it);// 将当前字符改写成大写形式  *it 解引用迭代器 得到其所指向的 对象  是其指向对象的别名 引用
	}

	// 字符串的第一个单词 改写成大写
	for (auto it = s.begin(); it != s.end() && !isspace(*it); ++it)
		*it = toupper(*it);

	// 迭代器类型  iterator (具有读写功能)  const_iterator 具有 读功能  不具有写功能
	// 对象为常量 只具有常量类型的迭代器 const_iterator  对象为变量具有 iterator 和 const_iterator
	vector<int>::iterator it;// 迭代器 it 可以读写 vector<int> 类型容器 的元素
	 string::iterator it2;   // it2 可以读写  string对象 中的字符
	 vector<int>::const_iterator it3;//it3只能读元素，不能写元素
	 string::const_iterator it4;     //it4只能读字符，不能写字符

	 // cbegin()   cend() 返回 常量 迭代器 仅能读取 容器元素 不能修改
	 vector<int> iv;        // 变量
	 const vector<int> civ; // 常量
	 auto it1 = iv.begin(); //  it1的类型为 vector<int>::iterator  能读写iv的元素
	 auto it2 = iv.cbegin(); // it2的类型为 vector<int>::const_iterator  能读iv的元素 不能修改 iv的元素
	 auto it3 = civ.begin(); // it3的类型为 vector<int>::const_iterator  能读civ的元素 不能修改 civ的元素

	  // 访问 容器元素对象的 成员函数   (*it).empty  等同于 it->empty()  解引用 和成员访问
	  vector<string> text;
	  for (auto it = text.cbegin(); it !=text.cend() && !it->empty(); ++it)
		cout << *it << endl;

	  // 迭代器 运算
	  auto mid = iv.begin() + iv.size()/2; //指向容器的中间位置
	  if (it < mid) // 处理前半部分元素
	  
	// 两个迭代器相减 得到的类型为 带符号整数  difference_type

	// 常规二分查找算法
	// 升序数组 查找的元素  范围开始  结束 
	int BinarySearch(int *array, int key, int low, int high)
	{
	    int mid;
	    while (low <= high)//  缩小范围 
	    {
		mid = (low + high) / 2;//更新中间元素的 下标 
		if (key == array[mid])//中间元素是否 等于所查找的元素 
		    return mid+1;//相等 返回元素下标  
		else if (key < array[mid])//所查元素 比 中间元素小  则在 前区间查找 
		    high = mid - 1;//将区间 右侧 退后 到 中间元素下标前一个元素  搜索 范围为  low，mid-1
		else//所查元素 比 中间元素大 则 在后区间查找 
		    low = mid + 1;//将区间  左测 提至  中间元素下标后一个元素    搜索 范围 mid+1，high
	    }
	    return 0;
	}
	
	// 使用迭代器完成二分查找
	 vector<int> text// 升序容器
	 auto b = text.begin(), e = text.end();//起始 结束位置
	 auto mid = b + (e - b)/2;//中间位置
	 while(low <= end && *mid != key){
	 	if(key < *mid) e = mid - 1;//所查元素 比 中间元素小  则在 前区间查找
		else b = mid + 1;// 所查元素 比 中间元素大 则 在后区间查找
		mid =  b + (e - b)/2;//更新 中间位置
	 }
	
	// 使用索引[] 访问 计算vector对象元素索引   统计各个分数段上 出现的 成绩个数
	// 索引不能添加元素
	vector<unsigned> scores(11,0);//11个分数段， 0~9，10~19，...,90~99，100 计数值全部初始化为0
	unsigned grade;
	while (cin >> grade){
	if(grade <= 100) ++scores[grade/10];
	} 
	// 使用迭代器 访问 计算vector对象元素索引   统计各个分数段上 出现的 成绩个数
	vector<unsigned> scores(11,0);//11个分数段， 0~9，10~19，...,90~99，100 计数值全部初始化为0
	unsigned grade;
	auto it0 = scores.begin();
	while (cin >> grade){
		auto it = it0 +  grade/10;
		if(grade <= 100) ++*it;
	} 
	
	
	
# 数组 
>  数组与标准库 类型 vector 类似，都存放类型相同对象的容器。
>  需要通过其所在的位置访问对象。
>  与vector不同的是，数组大小确定不变，不能随意向数组中增加元素, 数组不允许拷贝，vector允许拷贝。
>  注意数组名 相当于数组首元素的地址   ia[10]  ia === &ia[0]

## 【1】定义

	constexpr unsigned sz = 42;//constexpr修饰，常量表达式
	int arr[10];  //字面值常量初始化  含有10个整数的数组
	int arr2[sz]; //常量表达式初始化 含有42个个整数的数组
	int *parr[sz];//常量表达式初始化 含有42个指向整数的指针的数组

	定义时必须指定数组类型，不能由auto来推断
	不存在引用的数组，引用不是对象！！！
	string nums[] = {"one", "two", "three"};// 数组元素是string对象
	string *sp = &nums[0];// p指向nums的第一个元素
	string *sp2 = nums;   // 等价于 string *sp2 = &nums[0]

	auto sp3(nums); //sp3 是一个string指针，指向nums的第一个元素
	// 而decltype关键字 声明的 不发生上述转换
	 decltype(nums) sa = {"two", "three", "four"};//sa 是一个 含有3个string对象的 数组


##【2】显式初始化数组元素

	const unsigned sz = 3;//
	int ia1[sz] = {0, 1, 2};//列表初始化 含有3个元素
	int ia2[] = {0, 1, 2};//维度为3
	int ia3[5] = {0, 1, 2};//等价于 {0, 1, 2, 0, 0}

	// 字符数组
	char ca1[] = {'C', 'P', 'P'};//列表初始化
	char ca2[] = {'C', 'P', 'P', '\0'};//含有显式的 空字符
	char ca3[] = "CPP";//字符串字面值初始化 自动添加表示字符串结束的空字符

	// string 对象初始化 字符数组
	string s("Hello World");
	const char *str = s.c_str();// 用string对象初始化 字符数组 需要使用 c_str() 方法 最好再重新拷贝一份

	// 数组  初始化 vector 对象
	int i_arr[] = {1, 2, 3, 4, 5, 6};
	vector<int> ivec(begin(i_arr), end(i_arr));//全部副本
	vector<int> sub_ivec(i_arr + 1, i_arr + 4);// 包含 {2, 3, 4, 5}四个元素



	// 不允许拷贝和赋值
	char ca4 = ca3;// 错误

	// 复杂的数组声明定义
	int *parr[10];// 是数组，包含10个整形指针的数组
	int &rarr[10]=?;//错误，不存在 引用数组，引用不是对象
	int (*Parray)[10] = &arr;//是指针，指向一个含有10个整数的数组
	int (&Rarray)[10] = arr;//是引用，引用一个含有10个整数的数组	
	
## 【3】访问数组元素
### 与标准库类型vector 和 string 一样，数组元素也可以使用 范围for语句
### 或下标运算符 访问，元素下标从0开始，下标通常定义为 size_t类型,unsigned类型。
### 标准库类型vector 和 string 下标运算符索引必须为正值 unsigned类型，数组下标运算符索引 为signed类型，内置类型，可以为负值

	//下标访问修改元素
	unsigned score[11];//11个分数段
	unsigned grade;
	while(cin >> grade){
	    if(grade <= 100) ++score[grade/10];//对应段 计数+1
	}
	// 范围for 访问修改所有元素
	for( auto i:score)//可以设置为 引用就可以修改元素了
	    cout << i << " ";
	cout << endl;

	// 指针访问数组
	int iarr[] = {0,1,2,3,4};//含有5个元素
	int *pi = iarr;//指向第一个元素的指针 iarr[0]
	int *pi2 = iarr + 2;//指向第三个元素的指针 iarr[2]
	auto num = end(iarr) - begin(iarr); // num的值是5 就是iarr包含元素的数量 ptrdiff_t 类型 是signde类型 结果可能为负
	++pi;//指向第二个元素 iarr[1]
	j = pi[1];   // 等价于 *(p+1),就是 iarr[2], 就是 2
	k = pi[-1];  // 等价于 *(p-1),就是 iarr[0], 就是 0
	pi + 3;//指向最后一个元素
	*pi;//第二个元素 4
	int last =  *(iarr + 4);// 等价于 last = iarr[4];
	int *end = &iarr[6];//指向尾后的位置 到达不了    不能执行解引用运算！！！！！
	// 使用 for 
	fot(int *begin = arr; begin != end; ++begin)
		cout << *begin  << endl;//输出每一个元素
	// 使用 while
	while(begin<end){//指针指向相关的对象 可以比较大小（单位（间隔）一样大）
		cout << *begin  << endl;//输出每一个元素
		++begin;
	}

	//标准库函数 begin() end() 函数得到指针
	int iarr = {0,1,2,3,4};//函数5个元素
	int *beg = begin(iarr);//首元素指针
	int *end = end(iarr);//尾后指针                 不能执行解引用运算！！！！！
	while(beg != end && *beg >=0) ++beg;//找第一个负值元素

## 多维数组 数组的数组

### 初始化
	constexpr size_t row =3, col = 4;
	int iarr[row][col];//定义未初始化

	//下标运算符（size_t 类型） for 循环初始化
	for(size_t i = 0; i != row; ++i){
		for(size_t j = 0; j != col; ++j){
			iarr[i][j] = i * col + j;//元素索引为其 值
			cout << iarr[i][j] << ' '; // 访问输出  数组元素
			}
		 cout << endl;	
	}

	// 范围for 初始化
	size_t cnt = 0;
	for (auto &row1 : iarr)//每一行 引用  int (&row1)[4] 是引用 引用一个含有4个整数的数组
	 {	
		for (auto &col1 : row1){// int &col1 每一行的每一个元素 引用  可以读写 除去最内层外 其它必须使用 引用
		col1 = cnt;//赋值
		cout << col1 << ' ';// 访问 输出数组元素
		++cnt;
		}
		cout << endl;
	 }	
		
### 访问 
	// 指针访问
	int (*p)[4] = iarr;//p 指向一个含有4个整数的数组 iarr的 第一行   圆括号必不可少
	p = &iarr[2]; // iarr的 第3行
	// for 循环访问
	for( auto p = ia; p != ia + row; ++p){// 相当于定义 int (*p)[4] = iarr; p 指向 含有4个整数的数组
		 for( auto q = *p; q != *p + col; ++q) // *p 为含有4个元素的数组 q指向数组的首元素，即指向一个整数 int *q = *p
			cout << *q << ' ';
		 cout << endl;
	}
	// 使用 标准库函数 begin() 和 end()
	for( auto p = begin(ia); p != end(ia); ++p){// 相当于定义 int (*p)[4] = iarr; p 指向 含有4个整数的数组
		 for( auto q = begin(*p); q != end(*p); ++q) // *p 为含有4个元素的数组 q指向数组的首元素，即指向一个整数 int *q = *p
			cout << *q << ' ';
		 cout << endl;
	}	
	// 使用类型别名
	using int_arr_tpye = int[4];// int_arr_tpye为包含4个元素的整形数组
	typedef int int_arr_tpye[4];// 效果同上
	for( int_arr_tpye *p = ia; p != ia + row; ++p){// 相当于定义 int (*p)[4] = iarr; p 指向 含有4个整数的数组
		 for( int *q = *p; q != *p + col; ++q) // *p 为含有4个元素的数组 q指向数组的首元素，即指向一个整数
			cout << *q << ' ';
		 cout << endl;
	}


# 函数 
包括：返回类型 函数名字（形参列表） 函数体，函数的返回类型不能是数组或函数类型，但可以是 数组或函数类型的指针

## 函数定义  阶乘函数

	int fact(int val){
		int ret = 1;
		while(val >1) ret *= val--;
		return ret;// 返回主调函数 结束函数调用
	}
	
## 函数调用 分两步 1 实参初始化形参（形参为引用时，直接使用实参）  2控制权转移给被调用函数（inline 内联函数 之间在原处展开函数）
 
	int main(){
	int j = fact(5);// 实参5 初始化 形参（int val）
	cout << "5! = " << j << endl;
	return 0;
	}
	

## 局部对象
> 形参和函数体内定义的变量统称为 局部变量，仅在函数的作用域内可见， 局部自动对象，只存在于函数体执行期间，而局部静态对象，可在函数调用后一直存在

	// 定义
	int count_call(void){
	 int c =0;        //局部自动对象 每一次调用都初始化为 0  
	 static int sc =0;//局部静态变量 第一次调用初始化为0 以后每次调用在前一次值上 +1 
	 cout << ++sc << "   " << ++c << endl; 
	}
	// 调用
	int main(){
	 for(int i =0; i<10; ++i)  count_call(); //sc 输出 1 2,...10，c 输出一直是1
	 return 0;
	}
## 分离式编译 函数声明 与函数定义类似但是 不包括函数体，以;代替函数体 int fact(int val); 函数可以多次声明
	// 源文件 fact.cc
	#include "fact.h"
	int fact(int val){
		int ret = 1;
		while(val >1) ret *= val--;
		return ret;// 返回主调函数 结束函数调用
	}
	// 函数声明头文件 fact.h
	#ifndef FACT_H
	#define FACT_H
	int fact(int val);// 函数声明 
	#endif
	// 主函数调用 fact_main.c
	#include <iostream>
	#include "fact.h"
	using namespace std;
	int main(){
	int j = fact(5);// 实参5 初始化 形参（int val）
	cout << "5! = " << j << endl;
	return 0;
	}
	// 编译
	gcc fact_main.c fact.cc -o main
## 参数传递
> 当形参是引用类型时，为引用传递，实际传递的是实参的别名，没有进行拷贝，当实参的值被拷贝给形参时，形参和实参是两个独立的对象

### 值传递    函数对形参做的所有操作 都不会影响实参

	int n=0;
	int i = n;// n拷贝给i
	i = 42;//i的值改变， n的值不变    函数对形参做的所有操作 都不会影响实参 例如 fact(i) 不会改变i的值

### 引用传递  函数对形参做的所有操作 都会影响实参

	int n = 0;
	int &r_i = n;//r_i 是 n 的引用 即别名 同一个变量
	r_i = 42;//r_i 和 n 都变成 42    

### 指针形参

	int n=0, i =42;
	int *p_n = &n, *p_i = &i;// 指针
	*p_n = 100;// n 的值 变为100 指针p_n（变量你存储的地址） 不变
	p_n = p_i;// 现在 p_n  和  p_i 都指向了 i

	// 指针形参 函数
	void reset(int *pi){
	 *ip = 0;//改变了指针 pi 所指向的对象的值
	 ip = 0;// 值改变了 形参ip的值 实参未被改变
	}
	
	// 调用
	int i = 42;
	cout << "address of i =" << &i <<endl;
	reset(&i);// i 的值改变为0
	cout << "i = " << i << endl;// i 的值改变为0
	cout << "address of i =" << &i <<endl;// i 的存储地址未改变
	
	// C 程序中 通常使用 指针类型的形参 来访问和改变 函数外部的对象
	// C++ 程序中，建议使用引用类型的形参代替 指针形参，这样会更安全，也省时间（引用 无拷贝操作）
	
	// 使用 引用避免拷贝 拷贝大的类对象或容器 都比较低效 费时
	
### 引用形参

	 void reset(int &i){
	  i = 0;// 改变了i所引用的对象
	 }
	 // 调用
	 int j = 42;
	 reset(j);// 采样传 引用方式，它的值被改变 调用时 形参i 只是 实参j的一个别名，在函数reset内部对i的操作，即对j的使用
	 cout << "j = " << j << endl;

### 常量引用形参 当函数无须 改变引用参数的值时，最好将其声明为 常量引用

	// 比较两个字符串的长度
	bool isShorter(const string &rs1, const string &rs2){
		return rs1.size() < rs2.size();
	}

### 使用引用形参 返回额外信息

	// 函数返回多个值 返回字符在某个字符串中第一次出现的位置，并返回出现的 总次数
	string::size_type find_char(const string &crs, char c, string::size_type &occurs){
					// 字符串        查找的字符      出现的次数
		auto ret = crs.size();//初始化 第一次出现的位置
		occurs = 0;//初始化 出现的次数
		for(decltype(ret) i = 0; i != crs.size(); ++i){
		  if(crs[i] == c){// 出现字符 c
		    if (ret == crs.size())//位置 还未改变 为  第一次出现 
		    ret  = i;//记录第一次出现的位置
		    ++occurs;//出现次数 +1  通过形参引用间接返回 出现的次数
		  }
		}  
		return ret;//返回第一次出现的位置
	}

	// 调用
	string s("some string");
	string::size_type count = 0;
	auto index = find_char(s, 'o', count);

	// 判断 string对象是否是 一个句子
	 bool is_sentence(const string &crs){
		  // 如果 find_char() 的string参数 必须为 string & 那么不能直接把 const string & 带入
		  // 需要再定义一个 string对象， 另其为 crs 的副本，再带入
		 string::size_type count = 0;
		 return (find_char(crs, '.', count) == (crs.size() - 1)) &&  count == 1;
	 }

### 数组形参 必须确保使用数组时不会越界  通常需要给一个结束标志
1 不允许拷贝数组 2 在使用数组时会将其转换成指针（指向数组首元素的指针）

	// 三个函数等价 形参 都是 const int * 类型
	void print(const int*);
	void print(const int[]);
	void print(const int[10]);// 这里的维度表示期望数组含有多少元素，实际不一定
	//调用
	int i = 0;
	j[2] = {0, 1};
	print(&i); //&i 是int *类型 可以赋值给 const int *类型
	print(j);  //j 为 &j[0] 是 int * 类型

#### 使用标记指定数组长度   要求数组本身包含 一个结束标志  典型 C风格字符串 带有一个空字符

	// C风格字符串 带有一个空字符
	void print(const char *cp){
	  if(cp)// 确定 cp 不是一个空指针
	    while(*cp) // 只要 指针所指的字符不是 空字符
	       cout << *cp++;// 打印 字符
	}

#### 使用标准库规范 传递 数组元素的 首末地址

	void print(const int *beg, const int *end){
	  while(beg != end) 
	    cout << *beg++ << endl;//输出当前元素 并将指针向前移动一个位置
	}
	// 调用
	int j[2] =  {0, 1};
	print(begin(j), end(j));// 使用标准库 begin() 和 end() 函数

#### 显示传递 一个数组大小的形参
	void print(const int ia[], size_t size){
	  for (size_t i = 0; i != size; ++i) 
	     cout << ia[i] << endl;// 等价于 cout << *(ia+i) << endl;
	}
	// 调用
	int j[2] =  {0, 1};
	print( j, end(j) - begin(j) );// 使用标准库 begin() 和 end() 函数 做差来得到数组的大小

#### 数组引用形参 int (&r_arr)[10] 是一个含有10个元素数组的 引用  直接包含了 数组大小的信息

	void print(int (&r_arr)[10]){ // 注意形式 int (&r_arr)[10]   而 int &arr[10] 成了 包含引用的数组（还不存在，引用不是对象）
	  for (auto elem : r_arr)// 变量数组每个元素  范围for
	    cout << elem << endl;
	}
	// 调用 调用时 必须是 大小为10的整形 数组作为实参才可以
	int k[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
	print(k);// 大小必须为10 多一点 少一点 都不行

#### 多维数组形参 数组指针 形参
	void print(int (*p_arr)[10], int rowSize){}// 形参是 指向 一个含有10个整数的指针

### main函数 主函数参数列表
	// argc：argument counter 参数计数,argv：argument vector 参数 字符串 容器
	int main(int argc, char *argv[]){}
	int main(int argc, char **argv){}//第二个参数为 字符串数组 即数组的数组 指针的指针   argv 指向 char*
	//程序执行 program -d -o outfile data0
	则 argc = 5
	argv[0] = "program"; // 程序名
	argv[1] = "-d";      // 第一个参数 开始
	argv[2] = "-o";      // 第二个参数
	argv[3] = "outfile"; // 第三个参数
	argv[4] = "data0";   // 第四个参数  最后一个指针
	argv[5] = 0;   // 最后一个指针之后 的元素为0

### 含有可变形参的函数  1 传递一个 initializer_list 标准库类型，2 特殊参数类型 省略号 ...

#### initializer_list 形参  实参数量未知  但是全部实参类型 都 相同
	// initializer_list 提供的操作
	initializer_list<T> lst;// 默认初始化 T类型元素的空列表 模实际需要指定模板T的 具体类型
	initializer_list<T> lst{a, b, c...};// 列表中的元素是 const 常量
	lst2(lst); // 拷贝一个initializer_list对象，不会新建，原始列表 和 副本 共享元素
	lst2 = lst;// 同上
	lst.size();// 列表 中的元素
	lst.begin();//返回指向lst中首元素的指针
	lst.end();  //返回指向lst中尾元素下一个位置的指针
	// 因为有 begin() 和 end()对象可以使用 范围for 遍历参数

	// 具体
	initializer_list<string> ls ;//initializer_list 的元素类型是 string
	initializer_list<int> li ;   //initializer_list 的元素类型是 int
	// 和vector不同的是 initializer_list中的元素是常量 不能被修改

	// 定义函数
	void error_msg(initializer_list<string> ls){
		 for(auto beg = ls.begin(); beg != ls.end(); ++beg)
		   cout << *beg << " ";
		 cout << endl;
	}
	//调用函数
	//expected 和 actual 是string 对象
	if (expected != actual)
		error_msg({"function", expected, actual});
	else
		error_msg({"function", "okey"});
	// 传递了一个含有不同数量元素的 initializer_list

	// 定义函数 包含 ErrCode
	void error_msg(ErrCode e, initializer_list<string> ls){
		 cout << e.msg() << ": "
		 for(const auto &elem : ls )//范围for 遍历
		  cout << elem << " ";
		 cout << endl;
	} 

#### 省略符 ... 形参
	void foo(param_list, ...)//
	void foo(param_list...)//
	void foo(...)//
	
## 函数 返回类型 和 return语句
### 无返回值函数 void函数 无需显示的 return 语句   return 后无值
	// 交换两个值的函数
	void swap(int &r_i1, int &r_i2){
	   if (r_i1 == r_i2)// 两个值相等 无需交换
	      return;
	   // 若 执行 到这里，说明还需要继续完成下面的功能 
	   int temp = r_i1;//
	   r_i1 = r_i2;
	   r_i2 = temp;
	   // 此处 无需 显示的 return 语句   会隐式指向 return
	}
### 有返回值函数  return 后有值 且返回的对象类型 与 函数定义的 返回类型相同
	// 两个 string 对象是否 最短的部分 是相同的
	bool str_subrange(const string &str1, const string &str2){
	 if (str1.size() == str.size())
	     return str1 == str2; // 之间判断 相同长度间的部分是否相同
	 auto size = (str1.size() < str2.size()) ? str1.size() : str2.size(); //得到最短 字符串的 长度
	 for(decltype(size) i = 0; i != size; ++i){
	   if ( str1[i] != str2[i])// 如果 有 不相等的 字符 返回 false
	    return false;// 有 不相等的 字符 返回 false
	  }
	 return true; // 否者 相等 返回 true
	}
### 返回类型为 引用时 不会对结果进行拷贝 节省时间  但是 不要 返回 函数内部 临时变量的 引用， 临时变量离开函数后就不存在了
### 建议 返回 引用对象 是一个 调用函数 之前就纯在的一个变量
### 同时 返回 非常量的引用 可以作为 左值 被赋值

	// 不要 返回 函数内部 临时变量的 引用
	string temp("glo");
	const string &mainip() {
		 string ret("Empty"); // 函数内部临时变量
		 return ret; // 错误 ，不能返回 临时变量 作为 函数返回值的 引用
		 // return temp;// 返回 一个调用函数之前就出现的 变量 的引用     或者  参数 为引用类型的参数也可以
	}

	// 返回 两个字符串中 短的那个
	const string &shortString(const string &s1, const string &s2){// 返回 s1 或者 s2的引用
		return s1.size() < s2.size() ? s1 : s2;//返回 两个字符串中 短的那个
	}

	// 函数返回类型 为 标准库 类类型 可以直接调用 其成员函数
	auto sz = shortString(s1, s2).size()// 得到最短字符串 的长度

	// 返回 非常量的引用 可以作为 左值 被赋值  
	char &get_char(string &str, string::size_type id){
		return str[id];// 获取指定位置的 字符
	}
	// 调用
	string s("a value");
	cout << s << endl;// a value
	get_char(s, 0) = 'A';// 将s第一个位置上的字符 替换为 大写的 A
	cout << s << endl;// A value
	// 而返回为 常量引用 的不能被赋值
	shortString("hi", "bye") = "X"; // 错误 函数返回值是个 常量引用 不能被赋值


### 函数返回类型为 列表 以花括号 {} 包围
	vector<string> process(){
		if(expected.empty())
		  return {};// 返回一个 空vector对象
		else if (expected == actual)
		  return {"function", "okey"};
		else 
		  return {"function", expected, actual};
	}
### 函数递归  返回值为自身函数 的一个 式子   main 函数不能调用自己

	// 计算阶乘的函数
	int factorial( int val){
		if(val > 1)
		   return val * factorial(val-1);
		else 
		    return 1;
	}
	// 递归 返回一个vector的元素函数
	void print_vec(vector<int> vi){
		auto it = vi.begin();
		if(vi.size() > 1)
		 {
		   cout << *it <<endl;
		   vi.erase(it);
		   print_vec(vi);
		}
		else 
		   cout << *it <<endl;
	}

### 返回 数组 指针 数组不能被 拷贝 所以函数不能返回数组 但可以返回 数组的指针 或引用

	// 使用类别别名
	typedef int arrT[10];// arrT是一个类别别名 表示一个 含有 10个整数 的 数组
	using arrT = int[10];// 同上
	arrT* func(int i);   // 函数func 返回一个 指向 10个整数的数组的 指针

	//直接声明
	int arr[10]; //arr 是一个 含有 10个整数的数组
	int *arr_p[10]; //arr_p 是一个数组   含有 10个指整形针 的 数组
	int (*p2)[10] = &arr; // p2 是一个指针， 指向一个含有 10个整数的 数组 arr
	// 函数声明 类似
	Type (*function_name(parameter_list))[dimension]
	int ( *func(int i) )[10];// 声明一个函数 其形参为 int i ,返回类型 为 指针 ，指向 一个 含有 10个整数的 数组

	// 函数指针数组
	多个函数可以像数组一样被调用
	int (*fun_p_a[])(char *tmp); //函数指针数组

	// 使用 auto 和 尾置返回类型
	auto func(int i) -> int(*)[10];// 声明一个函数 其形参为 int i ,返回类型 为 指针 ，指向 一个 含有 10个整数的 数组

	// 使用 decltype 知道返回数组  类似类别别名 声明 定义
	int odd[] = {1, 3, 5, 7, 9};
	int even[] = {0, 2, 4, 6, 8};
	decltype(odd) *arrPtr(int i){ //使用decltype(odd) 表面类型与 odd类似
	 return (i%2) ? &odd : &even;// 返回一个指向数组的指针
	}

	// 声明一个 返回 引用 一个 含有10个string对象的数组 的函数
	string ( &func_r(string str) )[10];// 直接声明
	  // 使用类别别名
	typedef string arrS[10];// 类别别 含有10个string对象的数组
	using arrS = string[10];// 同上
	arrS &func(string str);   // 函数func 返回一个 指向 10个整数的数组的 指针
	  // 使用 auto 和 尾置返回类型
	auto func(string str) -> string(&)[10];
	  // 使用 decltype 知道返回数组  类似类别别名 声明 定义
	string str_arr[] = {"a string", "two"};
	decltype(str_arr) &arrPtr(string str);

## 函数 重载  同一个作用域内 的几个函数名字相同，但形参列表不同，成为 重载 (overloaded)
	// 打印 数组元素的 几个 同名函数
	void print(const char *cp);//出入参数为 带有结束符的 字符串指针
	void print(const int *beg, const int *end);//输入参数为 数组的首地址 和尾后地址
	void print(const int ia[], size_t size);//输入参数为 数组首地址和 数组大小信息
	int j[2] = {0, 1};
	print("Hello World");// 调用  print(const char *cp)
	print(begin(j), end(j));// 调用 print(const int *beg, const int *end)
	print(j, end(j) - begin(j));// 调用 print(const int ia[], size_t size)
> 函数重载 可以起到减轻 起名字、记名字的负担	 main() 函数不能重载
### 定义重载函数
> 一种数据库引用，记录 名字、电话、账户号码等信息

	Record lookup(const Account&); // 根据Account 查找记录  省略了 形参的名字
	Record lookup(const Phone&);   // 根据Phone   查找记录
	Record lookup(const Name&);    // 根据Name    查找记录
	Account acct;
	Phone   phond;
	Name    name;
	Record r1 = lookup(acct); // 接收  Account  的 版本
	Record r2 = lookup(phond);// 接收  Phone    的 版本
	Record r3 = lookup(name); // 接收  Name     的 版本
	// 函数重载 可以根据 实参 的类型 确定调用哪一个函数

	// 不允许两个函数 除了返回类型不同以外 其他都相同
	bool lookup(const Name&);    // 错误 冲突

	// 形参 的类型是否相同
	Record lookup(const Account&); // 根据Account 查找记录  省略了 形参的名字
	Record lookup(const Account& acct); //  错误 与上述定义重复
	typedef Phone Telno;
	Record lookup(const Phone&);   // 根据Phone   查找记录
	Record lookup(const Telno&);   //  错误 与上述定义重复

	// 形参 相差一个 顶层 const 为 重复定义
	Record lookup(Phone);
	Record lookup(const Phone);// 顶层const 不影响传入函数的对象 错误 与上述定义重复
	Record lookup(Phone* );
	Record lookup(Phone* const);// 顶层const 不影响传入函数的对象 错误 与上述定义重复	

	// 形参为 某种类型的 指针 或引用 呢可以通过 区分指向的 是常量 还是 非常量 实现函数重载
	Record lookup(Account&);// 非常量引用
	Record lookup(const Account&);//  新函数 常量引用
	Record lookup(Account*);// 非常量指针
	Record lookup(const Account*);//  新函数 常量指针
	
#### const_cast 和重载

	// 比较两个string 对象的长度，返回较短的那个引用 函数的参数和返回类型都是 const string 的 引用。
	// 对非常量的string实参 调用该函数，但返回的结果是 const string 的引用
	const string &shorterString(const string &s1, const string &s2){
		return s1.size() <= s2.size() ? s1 : s2;
	}

	// 使用 const_cast 重载shorterString()函数 使得当实参不是常量时，返回的是 一个非常量的 引用
	string &shorterString(string &s1, string &s2){
		auto &r = shorterString(const_cast<const string&>(s1), // 将实参强制转换成 const string 的 引用
					const_cast<const string&>(s2));// 调用上述形参为 const string& 的函数
		return const_cast<string &>(r);//强制转换成非常量引用
	}

## 特殊用途语言特性  函数默认实参 内联函数inline  常量表达式constexpr函数
### 函数默认实参  含有默认实参的函数，可以包含该实参，也可以省略该实参，省略时将使用默认实参的值 

	typedef string::size_type sz;// 类型别名
	string screen(sz ht = 24, sz wid = 80, char background = ' ');//为每一个形参提供了 默认实参
	// 需要注意的是，一旦某个形参被赋予了默认值，它后面的所有形参都必须配有默认值。
	// 调用
	string window;
	window = screen();             // 等价于 screen(24, 80, ' ')
	window = screen(66);           // screen(66, 80, ' ')
	window = screen(66, 256);      // screen(66, 256, ' ')
	window = screen(66, 256, '#'); // screen(66, 256, '#')
	window = screen('?');          // 只能省略尾部的实参 相当于 screen('?', 80, ' ') 与调用意图不符合
	// 在函数声明与定义中 形参的默认实参只能被赋予一次
	string screen2(sz, sz, char = ' ');// 定义 最后一个形参有默认实参
	string screen2(sz, sz, char = '*');// 错误 重复声明
	string screen2(sz = 24, sz = 80, char); //正确声明 添加 默认实参
	
### 内联函数 inline
#### 把规模较小的操作定义成函数有很多好处
	1】便于阅读和理解 理解 shorterString函数 比理解 等价的条件表达式容易的多
	2】使用函数可以确保 每次执行的 行为的 统一
	3】更易于修改计算过程 找函数去修改 更容易
	4】函数可以被其他应用重复利用，省去了重新编写的代价
       缺点： 函数比等价的条件表达式要慢一些，调用函数需要 保存寄存器，返回时恢复，可能需要拷贝实参，转向新的位置继续执行
#### 内联函数 inline 将函数在 原处 直接展开 避免调用 避免函数调用的开销
	// 定义内联函数
	inline const string &
	shorterString(const string &s1, const string &s2){
		return s1.size() < s2.size() ? s1 : s2;
	}
	//调用 内联函数
	cout << shorterString(s1, s2) << endl;
	// 相当于
	cout << (s1.size() < s2.size() ? s1 : s2) << endl;
	// inline 内联说明 只是向编译器 发出一个请求，清酒展开函数，但如果函数较复杂，或者函数较长，则编译器乐意选择忽略这个请求
### constexpr 函数 值能用于常量表达式的函数  函数的 返回值类型 和 形参类型都得是 字面值类型， 函数体内 必须 有且只有一个return
	constexpr int new_sz(){ return 42; }//
	constexpr int foo = new_sz(); // 正确，foo是一个常量表达式   常量 42  不能改变的量
	// constexpr 返回的不一定是 常量 
	constexpr size_t scale(size_t cnt) { return new_sz() * cnt; } // 如果参数是 常量则返回的也是常量，反之不一定
	int arr[scale(2)]; // 正确 scale(2) 是常量表达式
	int i = 2;         // i 是整形变量
	int a2[scale(i)];  // 错误 scale(i) 不是常量表达式，初始化数组时，必须使用常量表达式初始化数组

### 通常将 内联函数 和 constexpr 函数 的 声明和定义 都放在 头文件 .h文件中，因为他们的 多个定义必须一致

### 函数中 使用assert(expr) 宏 确保函数运行正确
	assert(dem>0);// 例如在 dem作为除数时 使用。 
	// expr 表达式 为 假时 输出信息并终止程序的执行，为真时 什么也不做，继续执行后面的程序
	assert(word.size() > threshold);// 确保输入的文本 单词的长度大于 某个阈值时 结束
### NDEBUG预处理变量
	// 如果 NDEBUG未定义 #ifndef 和 #endif之间的代码将被执行，反之，这些代码将被忽略 __func__  输出当前调试函数的名字
	void print(const int ia[], size_t size){
	#ifndef NDEBUG
		cerr << __func__ << ": array size is "<< zise << endl;
	#endif
	}

## 函数指针 函数指针指向的是函数 而非对象，函数的类型由 它的返回值类型 和 形参类型共同决定，与函数名无关
	// 比较 两个string 对象的 长度函数
	bool lengthCompare(const string &, const string &);
	// 该函数的类型是 bool(const string &, const string &) 声明一个之前该函数的指针，只需要用指针替换函数名即可
	bool (*Pf)(const string&, const string&); //指针未初始化  *pf 两端的括号不能少 
	// 返回值为 指针的 函数f
	bool *f(const string&, const string&);
	// 函数指针的初始化  使用函数名 自动转换成 指向函数的指针
	pf = lengthCompare;
	pf = &lengthCompare;// 同上式 等价  取地址符号是可选的
	// 函数的调用
	bool b1 = pf("hello", "goodbye");    		 // 三个等价的调用
	bool b2 = (*pf)("hello", "goodbye");     	 //  调用lengthCompare 获取结果
	bool b3 = lengthCompare("hello", "goodbye");     //
	// 不同函数类型的指针间不存在 转换规则
	
### 重载函数的指针
	void ff(int*);         //
	void ff(unsigned int); //
	void (*pf1)(unsigned int) = ff; // 该 函数指针 pf1 指向 ff(unsigned int) 函数
	void (*pf2)(int); // 错误 无对应形参的函数
	double (*pf3)(int*); // 错误 返回值类型也必须一样
### 函数指针 作为 另一个函数的 形参
	void useBigger(const string &s1, const string &s2,
		       bool pf(const string &, const string &));// 第三个参数是函数类型 会自动的转换成 函数的指针
	void useBigger(const string &s1, const string &s2,
		       bool (*pf)(const string &, const string &));// 显示的将形参定义成 指向函数的指针
	void useBigger(const string &s1, const string &s2, lengthCompare);// 直接使用原函数 作为实参使用 自动转成函数指针
#### 注意到 直接使用函数指针 显得冗长而烦琐  使用类型别名typrdef 和 类型声明 decltype 简化使用函数指针
	// Func 和 Func2是函数类型 的别名
	typedef bool Func(const string&, const string&);
	typedef decltype(lengthCompare) Func2;// 等价的类型
	// FuncP 和 FuncP2是 指向函数的指针 类型
	typedef bool (*FuncP)(const string&, const string&);
	typedef decltype(lengthCompare) *FuncP2;// 等价的类型
	// 使用类型别名
	void useBigger(const string &s1, const string &s2, Func);  // 第三个参数是函数类型 的类别别名 会自动的转换成 函数的指针
	void useBigger(const string &s1, const string &s2, FuncP2);// 显示的将形参定义成 指向函数的指针 的类别别名

### 函数的返回类型  为 指向函数的指针    函数不能返回函数  但可以返回 指向函数的指针
	// 定义类别别名
	using F = int(int*, int);     // F  是函数类型
	using PF = int(*)(int*, int); // PF 是指针类型 指向函数
	// 使用类别别名 定义函数 
	PF f1(int); // 正确 PF是指向函数的指针，f1 返回的类型为 指向函数的指针
	F f2(int);  // 错误 函数f2 不能返回函数类型
	F *f3(int); // 正确 显示的 指定返回类型是指向函数的指针
	// 直接定义
	int (*f1(int))(int*, int);
	// 使用尾置返回类型定义 返回函数指针的 函数
	auto f1(int) -> int (*)(int*, int);
	// 使用auto 和 decltype 定义函数
	string::size_type sumLength(const string&, const string&);
	decltype(sumLength) *getFcn(const string&);// decltype作用域某个函数时 仅返回函数类型 需要显示的 加上* 来表示 返回指针
#### 声明一个vector对象 器元素类型为 指向 一个函数的指针
	int func(int, int);        // 函数定义
	typedef decltype(func) *f; // 类型别名  using pf = int(*)(int, int);
	vector<f> v_f_p;// 定义 相应的 vector

	// 加减乘除 函数 定义
	int m_add(int a, int b){ return a + b;}
	int m_sub(int a, int b){ return a - b;}
	int m_mul(int a, int b){ return a * b;}
	int m_dev(int a, int b){if(b&&a) return a/b;}
	// 存储 函数指针的 容器
	using f = int(int, int);
	vector<f*> v_p_f;
	// 向容器内 添加元素
	v_p_f.push_back(m_add);
	v_p_f.push_back(m_sub);
	v_p_f.push_back(m_mul);
	v_p_f.push_back(m_dev);
	// 打印 容器的 元素
	for (auto p_f : v_p_f) cout << p_f << endl;
## IO输入输出
	istream 输入流类型，提供输入操作
	ostream 输出流类型，提供输出操作
	iostream 输入输出流
	ifstream 从文件读取数据
	ofstream 向文件写入数据
	fstream  读写文件
	istringstream 从string读取数据
	ostringstream 向string写入数据
	cin 	一个istream对象，从标准输入读取数据	
	cout
	cerr
	>> 右入
	<< 左出
	getline()函数

### IO对象无拷贝或赋值操作
	while(cin >> word) 确保IO操作不发生错误
	输出缓冲  os << "Please enter a value : ";
	刷新输出缓冲区 cout << "hi!" << endl; //输出一个 hi 和一个换行，然后刷新缓冲区
	cout << "hi!" << flush; //输出一个 hi 然后刷新缓冲区
	cout << "hi!" << ends; //输出一个 hi 和一个空字符，然后刷新缓冲区
	unitbuf 所有输出操作后，立刻刷新缓冲区 操作符 
	cout << unitbuf;// 即刻刷新缓冲区模式
	cout << nounitbuf;//正常模式

### 文件流对象
	ifstream in(file_name);//打开文件file_name 存入 in 文件流对象内
	ofstream out(file_output_name);//打开输出文件
	print(out, 变量);//打印到文件
	ofstream out2;//输出文件流未关联任何文件
	out2.open(file_name + ".copy");
	if(out2) {}//打开成功
	in.close();//关闭文件
	in.open("infile2","2");//打开另一个文件


# 动态内存
       动态内存：对象生命周期不定的内存管理技术。只有当显示的创建和释放时，才完成。
       全局对象，存放在（静态内存区）中，程序启动时分配，程序结束时销毁；
       对于局部自动对象，当进入程序时创建（在栈内存），离开函数时被销毁；
       静态对象存放在（静态内存）区，第一次使用前被创建，在程序结束时销毁。
       动态内存：对象生命周期不定的内存管理技术。只有当显示的创建和释放时，才完成。
       除了静态内存 和 栈内存，每个程序还有一个内存池，被称为自由空间（free store） 或者 堆（heap）；
       程序用堆来存储动态分配的对象。
       对象指针 = new 对象 ，分配内存；delete 对象指针 释放内存。但是有时会在尚有内存引用的情况下
       就释放了指针，会造成内存泄漏，段错误，核心已转存，俗称也指针。
       新标准库提供了两种智能指针，来动态管理对象，可以自动释放所指向的对象。

       shared_ptr 运行多个指针指向同一个对象；
       unique_ptr 独占所指向的对象；
       weak_ptr 伴随类，是一种若引用，指向 shared_ptr 所管理的对象。 都在memory的头文件中

## 动态内存 与智能指针
	类似vector，智能指针也是模板，因此当我们创建一个智能指针时，
	需要提供额外的信息，指针指向的对象的类型。
	
	shared_ptr<string> p1_ptr;// 默认初始化 一个空指针 null
	shared_ptr<vector<int>> vi_ptr;
	shared_ptr<list<double>> ld_ptr;
	unique_ptr<int> i_u_ptr;//
	
        // shared_ptr 和 new 一起使用
	boost::shared_ptr<pcl::RangeImage> range_image_ptr(new pcl::RangeImage);//范围图像 深度图像
	
	if(p) // 判断p是否初始化为一个实际的地址
	*p  解引用p 得到其指向的对象
	p->member  调用p指向对象的成员对象 或函数  等价于 (*p).member
	p.get()    返回p中保存的指针（地址）
	swap(q,p) 交换 p 和 q中的指针
	p.swap(q)
	
###  shared_ptr 独有的操作
	make_shared<T>(args)   返回一个shared_ptr, 指向一个动态分配的类型为T的对象，使用args初始化此对象
	shared_ptr<T>p(q)          p是shared_ptr类型 q 的拷贝，此操作会递增q中的计数器
	p = q                      此操作会递减p的引用计数，
				   而会递增q的引用计数，当p的引用计数变为0时，则将其指向的对象的内存释放
	p.use_count()  返回与p共享对象的智能指针数量，可能很慢，主要用于调试
	p.unique()     当p.use_count() 为1时返回 true；否者返回false

###   make_shared函数
	shared_ptr<int> ip = make_shared<int>(42);// ip 指向一个 值位42的int
	shared_ptr<srting> sptr = make_shared<string>(10, '9');// sptr指向一个值为 "99999999"的string
	shared_ptr<int> iptr = make_shared<int>();//iptr指向0
	auto vsp = make_shared<vector<string>>(); // vsp指向一个动态分配的空的 vector<string>
###  shared_ptr 的拷贝和赋值 会记录有多少个shared_ptr对象指向了相同的对象
	auto p = make_shared<int>(42);// p指向的对象只有p一个引用对象
	auto q(p); // p 和 q指向相同的对象，此对象有两个引用者，此操作会递增q中的计数器
	auto r = make_shared<int>(45);//  r指向一个int对象
	r = q; //给r赋值，令它指向另一个地址
	       //递增q指向对象（shared_ptr 的 int 42）的引用计数
	       //递减原来r指向的对象 （shared_ptr 的 int 45）的引用计数
	       // r 原来指向的对象已经没有引用者了，会自动释放，45被释放，通过int类的析构函数执行。
	// 可以认为每一个 shared_ptr对象 都有一个关联的计数器，通常称为引用计数（reference count）
        // 
	StrBlob b1; // 空 Blob
	{//新 的作用域
	      StrBlob b2 = {"a", "an", "the"}; //局部对象
	      b1 = b2;// b1和b2共享相同的元素
	      b2.push_back("about");  
	} // b2被销毁了，但是b2指向的元素未被销毁 StrBlob含有动态管理内存实现 
	// b1 含有 4个string的vector
	
#### my_StrBlob.h  使用 shared_ptr 实现 共享 vextor<string> 对象

	#ifndef MY_STRBLOB_H  
	#define MY_STRBLOB_H  
	#include <vector> 
	#include <string> 
	#include <memory>//shared_ptr 等动态内存管理技术
	#include <initializer_list>  //函数初始化列表
	#include <stdexcept> //错误捕捉 
	using std::vector;  //命名空间 声明
	using std::string;  
	using std::shared_ptr;  
	using std::make_shared;  
	using std::initializer_list;  
	using std::out_of_range;  

	class StrBlob{  
	public:  
	    typedef vector<string>::size_type size_type;//类型别名
	    StrBlob();//默认构造 
	    StrBlob(initializer_list<string> il);  //含有参数列表
	    size_type size() const { return data->size(); } //显示大小
	    bool empty() const { return data->empty(); }  // 为 空？
	    void push_back(const string &t) {data->push_back(t); } //添加元素
	    void pop_back(); // 删除元素
	    string& front(); //前置   访问元素
	    const string& front() const;  
	    string& back(); // 后置
	    const string& back() const;  

	private:  
	    shared_ptr<vector<string>> data;  // 私有变量 共享内存 共享变量
	    void check(size_type i, const string &msg) const;  
	}; 

	StrBlob::StrBlob(): data(make_shared<vector<string>>()) { } // 创建动态内存变量 指针 data
	StrBlob::StrBlob(initializer_list<string> il): data(make_shared<vector<string>> (il)) { }//传入参数

	void StrBlob::check(size_type i, const string &msg) const // 检查 并打印消息
	{  
	    if (i >= data->size())  // 大小超过范围
		throw out_of_range(msg);  
	}  
	string& StrBlob::front()  
	{  
	    check(0, "front on empty StrBlob");  
	    return data->front(); // vector的 front()的 方法
	}  
	const string& StrBlob::front() const  
	{  
	    check(0, "front on empty StrBlob");  
	    return data->front(); //返回常量引用
	}  
	string& StrBlob::back()  
	{  
	    check(0, "back on empty StrBlob");  
	    return data->back();  
	}  
	const string& StrBlob::back() const  // 对const 重载 const版本的实现
	{  
	    check(0, "back on empty StrBlob");  
	    return data->back();  
	}  
	void StrBlob::pop_back()  // 删除 元素
	{  
	    check(0, "pop_back on empty StrBlob"); 
	    return data->pop_back();  
	}  
	#endif  

##### my_StrBlob.cc 

	#include <iostream>  
	using std::cout;  
	using std::endl;  
	#include "my_StrBlob.h"  
	int main(int argc, char *argv[])  
	{  
		StrBlob b1;  
		{  //新作用域
			StrBlob b2 = {"a", "an", "the"};  
			b1 = b2;//b1 和  b3 共享内存  {"a", "an", "the", "about"}
			b2.push_back("about");  
			cout<<b2.size()<<endl;  
		}  
		cout<<b1.size()<<endl;  
		cout<<b1.front()<<" "<<b1.back()<<endl;  
		const StrBlob b3=b1;  
		cout<<b3.front()<<" "<<b3.back()<<endl;  
		return 0;  
	}  
#### 编写函数，返回一个动态分配的int的vector。将此vector传递给另一个函数。这个函数读取标准输入，将读入的值保存在vector中。再将vector传递给另一个函数，打印读入的值。记得在恰当的时刻delete vector。	
	#include <iostream>
	#include <vector>
	#include <new>
	using std::cin;
	using std::cout;
	using std::endl;
	using std::vector;
	using std::nothrow; 
	vector<int> *new_vector(void)//使用new 创建共享内存
	{
	    return new (nothrow) vector<int>; //如果分配失败，new返回一个空指针 不要抛出 std::bad_alloc 异常
	}
	void read_ints(vector<int> *pv)// 存储对象
	{
	    if(pv == NULL) return;
	    int v; 
	    while(cin>>v)
		pv->push_back(v);
	}
	void print_ints(vector<int> *pv)//打印对象
	{
	   if(pv == NULL) return;
	   for (const auto &v : *pv) 
		cout<<v<<" ";  
	    cout<<endl;  
	}  

	int main(int argc, char *argv[])  
	{  
	    vector<int>* pv =new_vector();  
	    if(!pv){  
			cout<<"Insufficient memory"<<endl;  
			return -1;  
	    }  
	   read_ints(pv);//读入数据
	   print_ints(pv);//打印数据
	   delete pv;//释放内存 
	   //cout << *pv << endl;
	   //print_ints(pv);// 已经释放了内存 而指针未置空 还进行解引用会造成内存泄漏 ！！！危险 
	   pv = nullptr;//指针设置为 NULL空 比便出现野指针
	   print_ints(pv);// 这时候 pv已经为 空指针了 就比较安全了 
	   return 0;  
	}
#### shared_ptr而不是内置指针 实现 动态分配的int的vector
	#include <iostream>  
	#include <vector>  
	#include <memory>  
	using std::cin;  
	using std::cout;  
	using std::endl;  
	using std::vector;  
	using std::shared_ptr;  
	using std::make_shared;  


	shared_ptr<vector<int>> new_vector(void)//创建对象 
	{  
	    return make_shared<vector<int>>();//make_shared 分配动态内存 
	}  

	void read_ints(shared_ptr<vector<int>> spv)//读入对象 
	{  
	    int v;  
	    while(cin>>v)  
		spv->push_back(v);  
	}  

	void print_ints(shared_ptr<vector<int>> spv)//打印对象 
	{  
	    for (const auto &v : *spv)  
		cout<<v<<" ";  
	    cout<<endl;  
	}  

	int main(int argc, char *argv[])  
	{  
	    auto spv = new_vector();  

	    read_ints(spv);
	    print_ints(spv);  
	    // 不用显示delete 和 赋null shared_ptr 会自动做 
	    return 0;  
	}   
#### new 动态分配内存 比较危险
	string* sptr = new string; // sptr指向一个初始化为空的 string，因为string为对象类型，且定义了构造函数
	int* iptr = neew int; // 而int为内置类型 无构造函数， 所有 iptr指向了一个未初始化的 int
	// 创建时 直接初始化
	int* ip = new int(1024);// ip指向的对象值为1024
	string* sp = new string(10, '9');// sp指向的对象为 "999999999"
	// 列表初始化
	vector<int>* vip = new vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};//包含10个元素
	// 值初始化 在类型名之后跟一对括号
	string* sp1 = new string;// 默认初始化 为 空string 对象string提供了默认构造函数
	string* sp2 = new string();//值初始化为空 string   还是使用 默认构造函数 初始化
	int* ip1 = new int;// 默认初始化 ip1指向了一个未初始化的int
	int* ip2 = new int();//值初始化为0 *ip2 为 0
	// 使用 auto
	auto p1 = new auto(obj);// p1指向一个与obj类型相同的 对象 若obj为int 则 p1位 int*
	// 使用const
	const int *cip = new const int(1024);//分配一个常量对象
	// 内存耗尽  当一个程序用光了它的可用内存 new 表达式就会失败 会跑出一个异常
	int* ip1 = new int();// 如果分配失败 new 会抛出 std::bad_alloc 异常
	int* ip2 = new (nothrow) int();//如果分配失败，new返回一个空指针 不要抛出 std::bad_alloc 异常
	// 我们称这种形式的 new （加了nothrow）为定位 new 可以判断 指针是否为空
#### delete 释放内存  delete之后记得 赋值为 空 NULL 重置指针  空悬指针（dangling pointer）
	int i, *ip1 = &i, *ip2 = NULL;
	double  *dp = new double(33), *dp2 = dp;
	delete i;//错误 i标志一个指针
	delete ip1;// 为定义， pil指向一个局部变量，不是动态变量
	delete dp;//正确 释放动态内存 33 的空间
	delete dp2;// 未定义， dp2指向的内存以及被释放了
	delete ip2;//正确, 释放一个空指针，总是没错的
	const int* cip = new const int(1024);//常量指针
	delete cip;//正确，释放一个const对象也是合理的
	//重置指针
	int* p(new int(42));//p 指向动态内存
	auto q = p; // q p 指向相同的内存
	delete p;// p q 均变为无效，指向的内存被释放
	p = nullptr; // p 重置为空
	q = nullptr; // q也需要重置为空

####  问题分析
	int *q = new int (42), *r = new int(100);  
	r = q;  
	auto q2 = make_shared<int> ()42, r2 = make_shared(100);  
	r2 = q2;  
	对于普通指针部分，首先分配了两个int型对象，指针分别保存在p和r中。
	接下来，将指针q的值赋予了r，这带来两个严重的内存管理问题：
	1.首先是一个直接的内存泄露的问题，r和q一样都指向42的内存地址，
	而r中原来保存的地址——100的内存再无指针管理，变成“孤儿内存”，从而造成内存泄漏。

	2.其次是一个“空悬指针“的问题。由于r和q指向同一个动态对象，如果程序编写不当，
	很容易产生释放了其中一个指针，而继续使用另一个指针的问题。
	继续使用的指针指向的是一块已经释放的内存，是一个空悬指针，
	继续读写它指向的内存可能导致程序崩溃甚至系统崩溃的严重问题。

	而shared_ptr则可很好地解决这些问题。首先，分配了两个共享的对象，
	分别由共享指针p2和g2指向，因而它们的引用计数均为1.接下来，将q2赋予r2,。
	赋值操作会将q2指向的对象地址赋予r2，并将r2原来指向的对象的引用计数减1，
	将q2指向的对象的引用计数加1。这样，前者的引用计数变为0，其占用的内存空间会被释放，
	不会造成内存泄露。而后者的引用计数变为2，也不会因为r2和q2之一的销毁而释放它的内存空间，
	因此也不会造成空悬指针的问题。	
#### shared_ptr 和 new 结合使用  但是更推荐 shared_ptr 和 make_shared结合使用
	// new 对象返回的是内置指针类型
	shared_ptr<int> p1 = new int(1024);// 错误 不能讲内置指针隐式转换为一个智能指针
	shared_ptr<int> p2(new int(1024));//正确 必须使用直接初始化的形式
	// 函数返回 shared_ptr 也必须显示绑定到 智能指针上
	shared_ptr<int> clone(int p){
	   //return new int(p);// 错误
	   return shared_ptr<int>(new int(p));//必须显示转换
		}
#### 智能指针 用来处理 未具有良好析构函数的类的 自动内存管理  传递一个删除器函数
	#include <iostream>  
	#include <memory>  
	using std::cout;  
	using std::endl;  
	using std::shared_ptr;  

	struct destination {};// 连接信息 
	struct connection {};// 连接对象 

	connection connect(destination *pd)  //打开连接  接收连接信息对象 
	{  
	    cout<<"open connection"<<endl;  
	    return connection();//返回 连接对象 类型 
	}  

	void disconnect(connection c)  //关闭连接   接收 连接对象 
	{  
	    cout<<"close connection"<<endl;  
	}  
	// 未使用shared_ptr版本  的打开连接处理函数 
	void f(destination &d)  
	{  
	    cout<<"manange connect directly"<<endl;  
	    connection c = connect(&d);  
	    // 忘记调用disconnect关闭连接   c就不会被关闭了 
	    cout<<endl;  
	} 

	// 提供给shared_ptr智能指针的 删除器函数 
	void end_connection(connection *p) { disconnect(*p); }  
	// 使用shared_ptr的版本  
	void f1(destination &d)  
	{  
	    cout<<"use shared_ptr to manage connect"<<endl;  
	    connection c = connect(&d);  
	    // shared_ptr<connection> p(&c, [](connection *p){ disconnect(*p);});  
	     // lambda代替end_connection函数。
	    shared_ptr<connection> p(&c, end_connection); //创建指针指针 并制定 删除器函数（类似析构函数的功能） 
	 // 该智能指针管理的内存，不是new 分配的内存，传递一个 删除器函数给他
	 // new创建的 会带有 构造和析构函数（如果对象有的话）
	    // 忘记调用disconnect关闭连接   而传递了 删除器函数的 指针指针会自动调用 删除器函数 进行内存释放操作 
	    cout<<endl;  
	}    
	int main(int argc, char *argv[])  
	{  
	    destination d;  
	    f(d); // 普通版本 不会 自动关闭（自动析构） 
	    f1(d);// 指针指针版本 在小程序运行后 会自动执行删除器函数 

	    return 0;  
	}  

### unique_ptr 独一无二的智能指针（霸王硬上弓）
	一个unique_ptr 拥有它所指向的对象，于shared_ptr 不同，某一时刻只能有一个 unique_ptr 指向一个给定的对象。
	当unique_ptr 被销毁时，它指向的对象也一起被销毁。
	unique_ptr 没有如unique_ptr指针的 make_shared 标准库函数 可以返回 一个 unique_ptr。
	unique_ptr 初始化时需要绑定到 一个new返回的指针上。
	
	unique_ptr<double> upd;//空
	unique_ptr<int> upi(new int(42));//upi指向一个值为42 的int
	// 因为 unique_ptr的 独特性（强占有特性），因此不知 拷贝 和 赋值
	unique_ptr<T> UPT;
	unique_ptr<T, D> UPT2;// T为类型  D为一个可调用对象来释放它的指针的对象类型的函数（类似析构函数，删除器）
	//可以通过release()来清空指针，使用reset来释放源指针指向的内存
	
	// 函数返回 unique_ptr<>
	unique_ptr<int> clone(int p){
	return unique_ptr<int> (new int(p));// 编译器会执行一种特殊的拷贝
	}
	//还可以返回 一个局部对象的拷贝
	unique_ptr<int> clone2(int p){
	unique_ptr<int> ret(new int(p));
	return ret;
	}
	
	// 使用shared_ptr的版本 传递  删除器
	void f1(destination &d)  
	{  
	    cout<<"use shared_ptr to manage connect"<<endl;  
	    connection c = connect(&d);  
	    // shared_ptr<connection> p(&c, [](connection *p){ disconnect(*p);});  
	     // lambda代替end_connection函数。
	    //shared_ptr<connection> p(&c, end_connection); 
	    //创建指针指针 并制定 删除器函数（类似析构函数的功能） 
	    unique_ptr<connection, decltype(end_connection)*> p(&c, end_connection);
	 // 该智能指针管理的内存，不是new 分配的内存，传递一个 删除器函数给他
	 // new创建的 会带有 构造和析构函数（如果对象有的话）
	    // 忘记调用disconnect关闭连接   而传递了 删除器函数的 指针指针会自动调用 删除器函数 进行内存释放操作 
	    cout<<endl;  
	}  	

### weak_ptr  是一种 不控制指向对象生存期的智能指针，指向一个由 shared_ptr 管理的对象  不参与管理  
	将一个  weak_ptr 绑定到一个 shared_ptr 上，不会改变 shared_ptr  的引用计数，
	一旦最后指向的对象  shared_ptr 被销毁，对象就会被释放，即使有  weak_ptr指向对象，对象也会被销毁
	
	// weak_ptr的创建  需要用一个 shared_ptr来初始化
	auto spi = make_shared<int>(42);
	weak_ptr<int> wpi(spi);// wpi弱共享spi，spi的引用计数未改变
	//由于 weak_ptr 指向的对象可能不存在 需要先判断
	if(shared_ptr<int> np = wpi.lock()){//如果 np不为空，则指向的对象 存在
	
	}


## 动态数组  new T[] 一个数组  动态数组    其实不是数组类型
	int* p = new int[42];//分配一个 42个int的数组，p指向第一个int
	// 类型别名
	typedef int arrT[42];// arrT表示一个int的数组类型
	int* p = new arrT;   // 作用 等同于  int* p = new int[42]; 
	//初始化
	int* pia = new int[10]; // 10个未初始化的int
	int* pia2 = new int[10]();//10个初始化为0的int
	string *psa = new string[10];//类对象会默认初始化 10个空的string
	string *psa2 = new string[10]();//显示初始化 10个空的string
	//列表初始化
	int* pia = new int[10]{0,1,2,3,4,5,6,7,8,9};
	string* psa = new string[10]{"a", "an", "the",string(3,'x')};//剩余的进行值初始化为空string
	//动态数组的释放
	delete [] pia;//pia指向一个动态分配的数组，按逆序释放数组元素

### 使用智能指针 unique_ptr 来管理动态数组
	//在类型名后必须跟一对方括号
	unique_ptr<int[]> upda(new int[10]);
	//可以使用下标运算符 来 访问 数组中的元素
	for(size_t i = 0; i != 10; ++i)  upda[i] = i;//位每个元素赋予一个新值

	upda.release();//自动调用 delete[] 来销毁其指针

### 使用智能指针 shared_ptr 来管理动态数组
	//shared_ptr 不直接支持 管理 动态内存，如果希望使用，必须提供一个自己定义的 删除器函数
	shared_ptr<int> sp(new int[10], [](int* p){delete[] p});//提供一个lambda定义的删除器函数
	// 是用get 获取一个内置指针来访问
	// shared_ptr 不支持 下标运算
	for(size_t i = 0; i != 10; ++i)  *(sp.get() + i)  = i;//使用get 获取一个内置指针来 间接 访问

### allocator 类

## 文本查询








