#include <iostream>
#include <vector>
#include <assert.h>  

/*
  vector C++ 11 ��������캯�� Ĭ�Ϲ��캯�� ��乹�캯�� 
  ��Χ���캯�� ���ƹ��캯�� �ƶ����캯��

  ��ֵ���ã�&& �����õ���ʱ��������ڸö��󱻳�ʼ��֮�����޸�
*/

/*��ֵ����*/

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

	//��ֵ���ñ���ʹ��ʵ��꣺��move<T>() 
	std::cout << is_r_value(std::move<int &>(i)) << std::endl;
}

 

// ����ֵ�йص��ƶ����캯��
// �ƶ����� ��Դ�������Դ����Ȩȫ������Ŀ�����

class Temp
{
public:
	Temp(const char* str = nullptr);
	Temp(Temp&& t); //�ƶ����캯��
	Temp& operator = (Temp&& t); //

	Temp(const Temp& t);       //���ƹ��캯��
	/*
	1�������ڴ���ʱʹ�������Ķ����ʼ��

	Person p(q); //��ʱ���ƹ��캯������������ʵ��p

	Person p = q; //��ʱ���ƹ��캯���������ڶ���ʵ��pʱ��ʼ��p

	2��������Ϊ�����Ĳ�������ֵ����ʱ

	f(p); //��ʱp��Ϊ�����Ĳ�������ֵ���ݣ�p��ջʱ����ø��ƹ��캯������һ���ֲ������뺯���ڵľֲ�����������ͬ��������

	��Ҫע����ǣ���ֵ��������ø��ƹ��캯������ֵֻ�Ǹ�ֵ�����(����)��������

	p = q; //��ʱû�и��ƹ��캯���ĵ��ã�

	�����ǵĻ����ǣ����������������ͬʱ����һ���Ѵ��ڵĶ��󸳸������ͻ���ø��ƹ��캯������������Ѿ����ڣ�Ȼ����һ���Ѵ��ڵĶ��󸳸��������õľ��Ǹ�ֵ�����(����)

	Ĭ�ϵĸ��ƹ��캯���͸�ֵ��������еĶ���"shallow copy"��ֻ�Ǽ򵥵ظ����ֶΣ������������к��ж�̬������ڴ棬����Ҫ�����Լ���д���ƹ��캯���������ظ�ֵ�������ʵ��"deep copy"��ȷ�����ݵ������ԺͰ�ȫ��
	*/
	Temp& operator = (Temp& t);//��ֵ����
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


//�ƶ���ֵ
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

//�������캯��
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

//size ����  size_type size() const;max_size0
//��������vector�Ĵ洢Ԫ�صĸ�������������ʵ�ʵ�����
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

//size ����  size_type size() const;max_size0
//��������vector�Ĵ洢Ԫ�صĸ�������������ʵ�ʵ�����

void myresize()
{
	std::vector<int> myvector;
	// set some initial content:
	for (int i = 1; i<10; i++) 
		myvector.push_back(i);
	myvector.resize(5);
	/*
	1��resize(n)���������ĳ��ȴ�С��ʹ��������n��Ԫ�ء�
       ���nС�������ĵ�ǰ��size����ɾ���������Ԫ�ء�
       ������Ӳ���ֵ��ʼ����Ԫ�ء�
	2��resize(n��t)
	   ��һ������t������������ӵ�Ԫ�س�ʼ��Ϊt��
	*/
	myvector.resize(8, 100);

	myvector.resize(12);
	std::cout << "myvector contains:";

	for (int i = 0; i<myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

}


/*
capacity����
size_type capacity() const;
��STL�У�ӵ��capacity���Ե�����ֻ��vector��string
����vector��ʵ�ʷ�����ڴ��С��ʾ�����£�
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

/*��size capacity������Ӧ��������������
ʹ��resize()�������ڵĶ����ڴ�ռ����������ڵġ�
ʹ��reserve()����ֻ���޸���capacity��ֵ�������ڵĶ���û����ʵ���ڴ�ռ�(�ռ���"Ұ"��)
  ������Խ������
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
�ı�vector������ʹ���vector�ĳߴ��С����
������
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
[]����������
reference operator[] (size_type n);
const_reference operator[] (size_type n) const;
��ȡvector��Ԫ�أ������C�л�ȡ����Ԫ��һ��
at����
reference at(size_type n);
const_reference at(size_type n) const;
��ȡvector�е�Ԫ�أ������[]������һ����������[]��ͬ���ǣ�at()����Ҫ������ı߽���м�飬���Խ��ͻ��׳��쳣������[]���ᡣ
front����
reference front();
const_reference front() const;
����vector���׸�Ԫ�ص�����
back ����
reference back();
const_reference back() const;
����vector��ĩβԪ�ص�����data ���� C++11
value_type* data() noexcept;
const value_type* data() const noexcept;
����ָ��vector�ڴ��ָ�롣
*/


/*
assign����
��C++11�ж���һ�� ��ʼ���б�ĺ���
initializer list (3)	void assign (initializer_list<value_type> il);
������������vector�����ݣ��滻֮ǰ�����ݡ�

������£�
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
push_back ����
void push_back (const value_type& val);
void push_back (value_type&& val); ��C++11��
��vector��ĩβ����һ��Ԫ�ء�
pop_back ����
void pop_back();
��vector��ĩβɾ��һ��Ԫ��
*/

/*insert ����
���е�move(4),initializer list(5) ��C++11�еĺ���
���������þ�����vector�в���һ�����߶��Ԫ�أ������ķ���ֵ��ָ�������Ԫ���еĵ�һ���ĵ�����
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
clear����
void clear();
���vector������Ԫ�أ�Ȼ��vector��size��С��Ϊ0

erase ���� 
iterator erase (iterator position);
iterator erase (iterator first, iterator last);
��������vector�е�һ������һ����Χ�ڵ�Ԫ�ء�
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
swap ����
void swap (vector& x);
���þ��ǽ�������vector�е�Ԫ��
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
emplace ������C++11��
template <class... Args>
iterator emplace (const_iterator position, Args&&... args);
��Ҳ��һ�����뺯��������ͬ����Ԫ����ͨ�������е�args����ģ�
�����
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
	emplace_back ����
	template <class... Args>
	void emplace_back (Args&&... args);
	�ں�����ĩβ���첢����һ����Ԫ�أ����������push_back�������ƣ���ͬ����push_back����ͨ�����ƻ���moveԪ�������롣
	ʾ���������
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
�������ĺ���
allocator_type get_allocator() const;
��������vector������ķ���������ĸ��ơ�
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
	rvalue_test(1); //��ֵ����

	return 0;
}