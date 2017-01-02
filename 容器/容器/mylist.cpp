/*
list test demo 
time:2017.1.2

���κ�λ�ò���ɾ�����ǳ���ʱ�䣬��֧�������ȡ�����˾�������˳���������еĳ�Ա�������⣬��֧��8����Ա������
push_front: ��ǰ�����
pop_front: ɾ��ǰ���Ԫ��
sort: ����( list ��֧��STL ���㷨sort)
remove: ɾ����ָ��ֵ��ȵ�����Ԫ��
unique: ɾ�����к�ǰһ��Ԫ����ͬ��Ԫ��
merge: �ϲ�������������ձ��ϲ����Ǹ�
reverse: �ߵ�����
splice: ��ָ��λ��ǰ�������һ�����е�һ������Ԫ��,������һ������ɾ���������Ԫ��
����һ��list
ʹ��list�ĳ�Ա����push_back��push_front����һ��Ԫ�ص�list��
list�ĳ�Ա����empty()
4��forѭ��������list�е�Ԫ��
5��STL��ͨ���㷨for_each������list�е�Ԫ��
6��STL��ͨ���㷨count_if()��ͳ��list�е�Ԫ�ظ���
7ʹ��count_if()��һ�����Ӹ��ӵĺ�������
8ʹ��STLͨ���㷨find()��list�в��Ҷ���
9ʹ��STLͨ���㷨find_if()��list����������
10ʹ��STLͨ���㷨search��list����һ������
11ʹ��list�ĳ�Ա����sort()����һ��list��
12��list�ĳ�Ա��������Ԫ�ص�list��
13List���캯��
14ʹ��list��Ա������list��ɾ��Ԫ��
15��list��Ա����remove()��list��ɾ��Ԫ�ء�
16ʹ��STLͨ���㷨remove()��list��ɾ��Ԫ��
17ʹ��STLͨ���㷨stable_partition()��list��Ա����splice()������һ��list
*/
#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
#include <string>
using namespace std;

//assign ���� �μ�vector�̳�
void myassign()
{
	int ary[] = { 1, 2, 3, 4, 5 };    
	list<int> l;       
	// assign to l the contains of ary    
	l.assign(ary,ary+5);       
	copy(l.begin(),l.end(),          
		ostream_iterator<int>(cout," "));   
	cout << endl;         
	l.assign(3,100);   // replace l for 3 copies of 100      
	copy(l.begin(),l.end(),             
		ostream_iterator<int>(cout," "));    
	cout << endl; 
}

//push_back push_front����
//push_back()��һ������ŵ�һ��list�ĺ��棬�� push_front()�Ѷ���ŵ�ǰ��
void  push_back_front()
{
	list<string> Milkshakes;
	Milkshakes.push_back("Chocolate");
	Milkshakes.push_back("Strawberry");
	Milkshakes.push_front("Lime");
    Milkshakes.push_front("Vanilla");
	for (auto i : Milkshakes)
		cout << i << " ";
	//�����Vanilla Lime Chocolate Strawberry
}

//back front����demo
template<class T,class D>
class Member
{
public:  
	Member(T t,D d):name(t), sal(d){}
	void print();
private:
	T name;
	D sal;
};

template<class T, class D>
void Member<T,D>::print()
{
	cout << name << " " << sal << endl;
}

void back_front_test()
{
	typedef Member<string, double> M; 
	list<M> l; 
	l.push_back(M("Robert", 60000));     
	l.push_back(M("Linda", 75000));
	list<M>::iterator It = l.begin();     
	cout << "Entire list:" << endl;      
	while (It != l.end())         
		(It++)->print();     
	cout << endl;       
	cout << "Return from back()" << endl;     
	l.back().print();
	cout << "Return from front" << endl;
	l.front().print();
	/*��������
	Entire list:
	Robert 60000
	Linda 75000

	Return from back()
	Linda 75000
	Return from front
	Robert 60000
	*/
}

//begin clear empty end ����

void bcee4()
{
	list<int> l;
	cout << "list is :";
	l.empty() ? cout << "null"<<endl : cout << "is not null"<<endl;
	l.push_back(1);
	cout << "list is :";
	l.empty() ? cout << "null" : cout << "is not null" << endl;
	for (auto i = 0; i < 5; i++)
		l.push_back(i);
	list<int>::iterator it = l.begin();
	cout << *it<<"  "<<endl;
	it = l.end();//end()ָ�����һ��Ԫ�ص���һ��λ�� ʵ���ϱ�ʾ�����ڵ�  ��Ҫȥend()Ԫ��
	it--;
	cout << *it << "  " << endl;
	l.clear();
	cout << "list is :";
	l.empty() ? cout << "null" << endl : cout << "is not null" << endl;
	/*�����
	list is :null
	list is :is not null
	1
	4
	list is :null
	*/
}

//insert erase size ����demo
//ͨ���㷨remove()ʹ�ú�list�ĳ�Ա������ͬ�ķ�ʽ������һ������²��ı������Ĵ�С��
void ies()
{
	list<int> l;
	cout<<"size="<<l.size()<<endl;
	l.insert(l.begin(),1);
	cout << "size=" << l.size() << endl;
	list<int>::iterator It;
	It = l.begin();
	l.erase(It);
	
	cout << "size=" << l.size() << endl;
}

//merge
void mymerge()
{
	int ary[] = { 2, 5, 9, 7, 2, 7, 6, 5 };   
	list<int> list1(ary, ary + 4);   
	list<int> list2(ary + 4, ary + 8);   
	cout << "list1 : ";    
	copy(list1.begin(), list1.end(),
		ostream_iterator<int>(cout, " "));   
	cout << endl;  
	cout << "list2 : ";    
	copy(list2.begin(), list2.end(), 
		ostream_iterator<int>(cout, " "));  
	cout << endl << endl;    
	// you have to sort data before megring it    
	list1.sort();    
	list2.sort();     
	list1.merge(list2);      
	cout << "After \"list1.merge(list2)\" :" << endl;   
	cout << "list1 : ";    
	copy(list1.begin(),list1.end(),            
		ostream_iterator<int>(cout, " "));
	cout << endl;     
	cout << "size of list2 = " << list2.size()<< endl;   
	cout << "list2 is " << (list2.empty() ? "" : "not ")<< "empty" << endl; 
	
	/*
	list1 : 2 5 9 7
	list2 : 2 7 6 5

	After "list1.merge(list2)" :
	list1 : 2 2 5 5 6 7 7 9
	size of list2 = 0
	list2 is empty
	*/
}
/*
����find()��һ����ǿ��İ汾�����������ʾ��find_if()��������һ����������Ĳ�����Ϊ��������ʹ�������������ӵ����۶����Ƿ�ͳ��Ĳ��������ึ���������ǵ�list����һЩ��������еİ������¼������ڵļ�¼������ϣ���ҳ�������1997����¼���
����find()��һ����ǿ��İ汾�����������ʾ��find_if()��������һ����������Ĳ�����Ϊ������ ��ʹ�������������ӵ����۶����Ƿ�͸����Ĳ��������ึ���������ǵ�list����һЩ��������еİ������¼������ڵļ�¼������ϣ���ҳ�������1997����¼���
��������[first,end)����ѰʹһԪ�ж�ʽpredΪtrue�ĵ�һ��Ԫ�ء�
���û�ҵ�������end��
*/

class EventIsIn1997
{
public:
	bool operator () (string& EventRecord)
	{
		// year field is at position 12 for 4 characters in EventRecord
		return EventRecord.substr(11, 4) == "1997";
	}
};

void findIf(void)
{
	list<string> Events;

	// string positions 0123456789012345678901234567890123456789012345
	Events.push_back("07 January 1995 Draft plan of house prepared");
	Events.push_back("07 February 1996 Detailed plan of house prepared");
	Events.push_back("10 January 1997 Client agrees to job");
	Events.push_back("15 January 1997 Builder starts work on bedroom");
	Events.push_back("30 April 1997 Builder finishes work");

	list<string>::iterator EventIterator = find_if(Events.begin(), Events.end(), EventIsIn1997());

	// find_if completes the first time EventIsIn1997()() returns true
	// for any object. It returns an iterator to that object which we
	// can dereference to get the object, or if EventIsIn1997()() never
	// returned true, find_if returns end()
	if (EventIterator == Events.end())
	{
		cout << "Event not found in list" << endl;
	}
	else
	{
		cout << *EventIterator << endl;
	}
	//���ǳ���������
	//10 January 1997 Client agrees to job

}


int main()
{
	//myassign();
	//push_back_front();
//	back_front_test();
//	ies();
	//mymerge();
	findIf();
	
	//bcee4();
	return 0;
}