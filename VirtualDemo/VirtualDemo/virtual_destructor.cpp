//destructor and structor demo

#include <iostream>

using namespace std;

class A
{
  protected:
	int a;

  public:

	A() :a(50) //initialize 
	{
		cout << "A ȱʡ���캯��: a=" << a << endl;
	}

	A(int i) :a(i)
	{
		cout << "A ���캯��: a=" << a << endl;
	}

	~A()
	{
		cout << "A ����������a=" << a << endl;
	}
};

class B1 :virtual public A
{

protected:

	int b1;

public:

	B1() :b1(60)
	{
		cout << "B1 ȱʡ���캯��: b1=" << b1 << endl;
	}

	B1(int i, int j) :A(i), b1(j)
	{
		cout << "B1 ���캯��: b1=" << b1 << endl;
	}

	~B1()
	{
		cout << "B1 ����������b1=" << b1 << endl;
	}

};

class B2 :virtual public A
{
protected:

	int b2;

public:

	B2() :b2(70)
	{
		cout << "B2 ȱʡ���캯��: b2=" << b2 << endl;
	}

	B2(int i, int j) :A(i), b2(j)
	{
		cout << "B2 ���캯��: b2=" << b2 << endl;
	}

	~B2()
	{
		cout << "B2 ����������b2=" << b2 << endl;
	}

};

class C :public B1, public B2
{
protected:
	int c;
public:

	C() :c(70)
	{
		cout << "C ȱʡ���캯��: c=" << c << endl;
	}

	C(int i, int j, int x, int y) :A(i), B1(i, j), B2(i, x), c(y)
	{
		cout << "C ���캯��: c=" << c << endl;
	}
	~C()
	{
		cout << "C ����������c=" << c << endl;
	}
};


class B3 : public A
{

protected:

	int b1;

public:

	B3() :b1(60)
	{
		cout << "B1 ȱʡ���캯��: b1=" << b1 << endl;
	}

	B3(int i, int j) :A(i), b1(j)
	{
		cout << "B1 ���캯��: b1=" << b1 << endl;
	}

	~B3()
	{
		cout << "B1 ����������b1=" << b1 << endl;
	}

};

class B4 : public A
{
protected:

	int b2;

public:

	B4() :b2(70)
	{
		cout << "B2 ȱʡ���캯��: b2=" << b2 << endl;
	}

	B4(int i, int j) :A(i), b2(j)
	{
		cout << "B2 ���캯��: b2=" << b2 << endl;
	}

	~B4()
	{
		cout << "B2 ����������b2=" << b2 << endl;
	}

};

class C1 :public B3, public B4
{
protected:
	int c;
public:

	C1() :c(70)
	{
		cout << "C ȱʡ���캯��: c=" << c << endl;
	}

	C1(int i, int j, int x, int y) :B3(i, j), B4(i, x), c(y)
	{
		cout << "C ���캯��: c=" << c << endl;
	}
	~C1()
	{
		cout << "C ����������c=" << c << endl;
	}
};

int main()
{
	C1 obj1;
	{
		C1 obj2(6, 7, 8, 9);
	}

	return 0;
}