#include <iostream>
#include <vector>
#include <assert.h>  

/*
  vector C++ 11 有五个构造函数 默认构造函数 填充构造函数 
  范围构造函数 复制构造函数 移动构造函数

  右值引用：&& 所引用的临时对象可以在该对象被初始化之后做修改
*/

/*右值测试*/

bool is_r_value(int &&)
{
	return true;
}

bool is_r_value(const int &)
{
	return false;
}

void rvalue_test(int &&i)
{
	std::cout << is_r_value(i) << std::endl;

	//右值引用必须使用实体店：：move<T>() 
	std::cout << is_r_value(std::move<int &>(i)) << std::endl;
}

 

// 跟右值有关的移动构造函数
// 移动构造 把源对象的资源控制权全部交给目标对象

class Temp
{
public:
	Temp(const char* str = nullptr);
	Temp(Temp&& t); //移动构造函数
	Temp& operator = (Temp&& t); //

	Temp(const Temp& t);       //复制构造函数
	/*
	1、对象在创建时使用其他的对象初始化

	Person p(q); //此时复制构造函数被用来创建实例p

	Person p = q; //此时复制构造函数被用来在定义实例p时初始化p

	2、对象作为函数的参数进行值传递时

	f(p); //此时p作为函数的参数进行值传递，p入栈时会调用复制构造函数创建一个局部对象，与函数内的局部变量具有相同的作用域

	需要注意的是，赋值并不会调用复制构造函数，赋值只是赋值运算符(重载)在起作用

	p = q; //此时没有复制构造函数的调用！

	简单来记的话就是，如果对象在声明的同时将另一个已存在的对象赋给它，就会调用复制构造函数；如果对象已经存在，然后将另一个已存在的对象赋给它，调用的就是赋值运算符(重载)

	默认的复制构造函数和赋值运算符进行的都是"shallow copy"，只是简单地复制字段，因此如果对象中含有动态分配的内存，就需要我们自己重写复制构造函数或者重载赋值运算符来实现"deep copy"，确保数据的完整性和安全性
	*/
	Temp& operator = (Temp& t);//赋值操作
	~Temp(void);
private:
	char *m_pData;
};


Temp::Temp(const char* str)
{
	if (!str)
	{
		m_pData = nullptr;
	}
	else
	{
		this->m_pData = new char[strlen(str) + 1];
		strcpy(this->m_pData, str);
	}
}


//移动赋值
Temp::Temp(Temp&& t) :m_pData(std::move(t.m_pData))
{
	t.m_pData = nullptr;
}


Temp& Temp::operator = (Temp&& t)
{
	assert(this != &t);

	this->m_pData = nullptr;
	this->m_pData = std::move(t.m_pData);
	t.m_pData = nullptr;

	return *this;

}

//拷贝构造函数
Temp::Temp(const Temp& t)
{
	if (!t.m_pData)
	{
		this->m_pData = nullptr;
	}
	else
	{
		this->m_pData = new char[strlen(t.m_pData) + 1];
		strcpy(this->m_pData, t.m_pData);
	}
}

Temp& Temp::operator = (Temp &t)
{
	if (this != &t)
	{
		delete[] this->m_pData;
		if (!t.m_pData)
		{
			this->m_pData = nullptr;
		}
		else
		{
			this->m_pData = new char[strlen(t.m_pData) + 1];
			strcpy(this->m_pData, t.m_pData);
		}
	}

	return *this;
}

Temp::~Temp(void)
{
	if (this->m_pData)
	{
		delete[] this->m_pData;
		this->m_pData = nullptr;
	}
}

//size 函数  size_type size() const;max_size0
//函数返回vector的存储元素的个数，而不是其实际的容量
void testSize()
{
	std::vector<int> myints;
	std::cout << "0. size: " << myints.size() << '\n';
	for (int i = 0; i<10; i++)
		myints.push_back(i);

	std::cout << "1. size: " << myints.size() << '\n';
	myints.insert(myints.end(), 10, 100);
	std::cout << "2. size: " << myints.size() << '\n';
	myints.pop_back();
	std::cout << "3. size: " << myints.size() <<'\n' << myints.max_size() << '\n';

}

//size 函数  size_type size() const;max_size0
//函数返回vector的存储元素的个数，而不是其实际的容量

void myresize()
{
	std::vector<int> myvector;
	// set some initial content:
	for (int i = 1; i<10; i++) 
		myvector.push_back(i);
	myvector.resize(5);
	/*
	1、resize(n)调整容器的长度大小，使其能容纳n个元素。
       如果n小于容器的当前的size，则删除多出来的元素。
       否则，添加采用值初始化的元素。
	2、resize(n，t)
	   多一个参数t，将所有新添加的元素初始化为t。
	*/
	myvector.resize(8, 100);

	myvector.resize(12);
	std::cout << "myvector contains:";

	for (int i = 0; i<myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

}


/*
capacity函数
size_type capacity() const;
在STL中，拥有capacity属性的容器只有vector和string
返回vector中实际分配的内存大小。示例如下：
*/

void mycapacity()
{
	std::vector<int> myvector;
	for (int i = 0; i<100; i++) 
		myvector.push_back(i);
	std::cout << "size: " << (int)myvector.size() << '\n';
	std::cout << "capacity: " << (int)myvector.capacity() << '\n';
	std::cout << "max_size: " << (int)myvector.max_size() << '\n';

}

/*与size capacity函数对应的两个函数如下
使用resize()，容器内的对象内存空间是真正存在的。
使用reserve()仅仅只是修改了capacity的值，容器内的对象并没有真实的内存空间(空间是"野"的)
  下面测试结果如下
v.size() == 0 v.capacity() = 0
v.size() == 0 v.capacity() = 10
v.size() == 11 v.capacity() = 15
*/

void res()
{
	std::vector<int> v;
	std::cout << "v.size() == " << v.size() << " v.capacity() = " << v.capacity() << std::endl;
	v.reserve(10);
	std::cout << "v.size() == " << v.size() << " v.capacity() = " << v.capacity() << std::endl;
	v.resize(10);
	v.push_back(0);
	std::cout << "v.size() == " << v.size() << " v.capacity() = " << v.capacity() << std::endl;
}

/*
void shrink_to_fit();
改变vector的容量使其和vector的尺寸大小符合
输出结果
1. capacity of myvector: 100
2. capacity of myvector: 100
3. capacity of myvector: 10

*/

void myshrink_to_fit()
{
	std::vector<int> myvector(100);
	std::cout << "1. capacity of myvector: " << myvector.capacity() << '\n';
	myvector.resize(10);
	std::cout << "2. capacity of myvector: " << myvector.capacity() << '\n';
	myvector.shrink_to_fit();
	std::cout << "3. capacity of myvector: " << myvector.capacity() << '\n';
}

/*
[]操作符函数
reference operator[] (size_type n);
const_reference operator[] (size_type n) const;
获取vector中元素，这个和C中获取数组元素一样
at函数
reference at(size_type n);
const_reference at(size_type n) const;
获取vector中的元素，这个和[]的作用一样，不过和[]不同的是，at()函数要对数组的边界进行检查，如果越界就会抛出异常，但是[]不会。
front函数
reference front();
const_reference front() const;
返回vector中首个元素的引用
back 函数
reference back();
const_reference back() const;
返回vector中末尾元素的引用data 函数 C++11
value_type* data() noexcept;
const value_type* data() const noexcept;
返回指向vector内存的指针。
*/


/*
assign函数
在C++11中多了一个 初始化列表的函数
initializer list (3)	void assign (initializer_list<value_type> il);
函数重新设置vector的内容，替换之前的内容。

结果如下：
Size of first: 7
Size of second: 5
Size of third: 3
*/
void myassign()
{
	std::vector<int> first;
	std::vector<int> second;
	std::vector<int> third;
	first.assign(7, 100);             // 7 ints with a value of 100

	std::vector<int>::iterator it;
	it = first.begin() + 1;

	second.assign(it, first.end() - 1); // the 5 central values of first

	int myints[] = { 1776, 7, 4 };
	third.assign(myints, myints + 3);   // assigning from array.

	std::cout << "Size of first: " << int(first.size()) << '\n';
	std::cout << "Size of second: " << int(second.size()) << '\n';
	std::cout << "Size of third: " << int(third.size()) << '\n';

}

/*
push_back 函数
void push_back (const value_type& val);
void push_back (value_type&& val); （C++11）
在vector的末尾插入一个元素。
pop_back 函数
void pop_back();
在vector的末尾删除一个元素
*/

/*insert 函数
其中的move(4),initializer list(5) 是C++11中的函数
函数的作用就是在vector中插入一个或者多个元素，函数的返回值是指向插入新元素中的第一个的迭代器
*/

void myinsert()
{
	std::vector<int> myvector(3, 100);
	std::vector<int>::iterator it;

	it = myvector.begin();
	it = myvector.insert(it, 200);
	myvector.insert(it, 2, 300);

	// "it" no longer valid, get a new one:
	it = myvector.begin();

	std::vector<int> anothervector(2, 400);
	myvector.insert(it + 2, anothervector.begin(), anothervector.end());

	int myarray[] = { 501, 502, 503 };
	myvector.insert(myvector.begin(), myarray, myarray + 3);

	std::cout << "myvector contains:";
	for (it = myvector.begin(); it<myvector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';

}
/*
clear函数
void clear();
清除vector中所有元素，然后vector的size大小变为0

erase 函数 
iterator erase (iterator position);
iterator erase (iterator first, iterator last);
函数移走vector中的一个或者一定范围内的元素。
*/

void myerase()
{
	std::vector<int> myvector;
	// set some values (from 1 to 10)
	for (int i = 1; i <= 10; i++) myvector.push_back(i);
	// erase the 6th element
	myvector.erase(myvector.begin() + 5);
	// erase the first 3 elements:
	myvector.erase(myvector.begin(), myvector.begin() + 3);
	std::cout << "myvector contains:";
	for (unsigned i = 0; i<myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

}

/*
swap 函数
void swap (vector& x);
作用就是交换两个vector中的元素
*/

void myswap()
{
	std::vector<int> foo(3, 100);   // three ints with a value of 100
	std::vector<int> bar(5, 200);   // five ints with a value of 200
	foo.swap(bar);
	std::cout << "foo contains:";
	for (unsigned i = 0; i<foo.size(); i++)
		std::cout << ' ' << foo[i] <<std::endl;
	std::cout << "bar contains:";
	for (unsigned i = 0; i<bar.size(); i++)
		std::cout << ' ' << bar[i] << std::endl;
}

/*
emplace 函数（C++11）
template <class... Args>
iterator emplace (const_iterator position, Args&&... args);
这也是一个插入函数，但不同的新元素是通过参数中的args构造的，
结果：
myvector contains: 10 200 100 20 30 300
*/

void myemplace()
{
	std::vector<int> myvector = { 10, 20, 30 };
	auto it = myvector.emplace(myvector.begin() + 1, 100);
	myvector.emplace(it, 200);
	myvector.emplace(myvector.end(), 300);
	std::cout << "myvector contains:";
	for (auto& x : myvector)
		std::cout << ' ' << x;
	std::cout << '\n';

}
/*
	emplace_back 函数
	template <class... Args>
	void emplace_back (Args&&... args);
	在函数的末尾构造并插入一个新元素，这个函数和push_back函数类似，不同的是push_back函数通过复制或者move元素来插入。
	示例：结果：
	myvector contains: 10 20 30 100 200
*/
void myemplace_back()
{
	std::vector<int> myvector = { 10, 20, 30 };
	myvector.emplace_back(100);
	myvector.emplace_back(200);
	std::cout << "myvector contains:";
	for (auto& x : myvector)
		std::cout << ' ' << x;
	std::cout << '\n';

}
/*
分配器的函数
allocator_type get_allocator() const;
函数返回vector相关联的分配器对象的复制。
*/
void myallocated()
{
	std::vector<int> myvector;
	int * p;
	unsigned int i;
	// allocate an array with space for 5 elements using vector's allocator:
	p = myvector.get_allocator().allocate(5);
	// construct values in-place on the array:
	for (i = 0; i<5; i++)
		myvector.get_allocator().construct(&p[i], i);
	std::cout << "The allocated array contains:";
	for (i = 0; i<5; i++)
		std::cout << ' ' << p[i];
	std::cout << '\n';
	// destroy and deallocate:
	for (i = 0; i<5; i++) myvector.get_allocator().destroy(&p[i]);
	myvector.get_allocator().deallocate(p, 5);

}

int main()
{
	//testSize();
	//myresize();
	//mycapacity();
	//res();
	//myshrink_to_fit();
	//myassign();
	myinsert();
	rvalue_test(1); //右值测试

	return 0;
}