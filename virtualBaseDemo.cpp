//virtual base class pratice 
#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std;

class A
{
 protected:
  	int a;
 public:
   A():a(50){}
   void print()
   {
   cout<<"A "<<a<<endl;
   }
};
 
class B1:virtual public A
{
protected:
   int b1;
public:
   B1():b1(60){}
   void g()
   {
   a=10;
   cout<<"B1"<<b1<<" "<<a<<endl;
   }
};
 
class B2:virtual public A
{
protected:
   int b2;
public:
   B2():b2(70){}
   void g()
   {
   	a=20;cout<<"B2 "<<b2<<endl;
   }
};
 
class C:public B1, public B2
{
protected:
   int c;
public: 
   C():c(80){}
   void g(){a=30;b1=40;b2=50;cout<<a<<" "<<b1<<" "<<b2<<endl;}
   /*�����ĳ�Ա�ڽ�һ�����������к�������һ��ά��ͬһ���ڴ����ݿ���,
     ����a����ֻ����Ψһ��һ��������ʹ�������������*/
};
 
int main()
{
   C d1;
   /*ʹ����������D������ֻ����һ�������A���Ӷ�������d1.print()�ǺϷ���*/
   d1.print();
   d1.B1::g();
   d1.B2::g();
   d1.g();
 
   return 0;
}
