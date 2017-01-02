/*
list test demo 
time:2017.1.2

在任何位置插入删除都是常数时间，不支持随机存取。除了具有所有顺序容器都有的成员函数以外，还支持8个成员函数：
push_front: 在前面插入
pop_front: 删除前面的元素
sort: 排序( list 不支持STL 的算法sort)
remove: 删除和指定值相等的所有元素
unique: 删除所有和前一个元素相同的元素
merge: 合并两个链表，并清空被合并的那个
reverse: 颠倒链表
splice: 在指定位置前面插入另一链表中的一个或多个元素,并在另一链表中删除被插入的元素
定义一个list
使用list的成员函数push_back和push_front插入一个元素到list中
list的成员函数empty()
4用for循环来处理list中的元素
5用STL的通用算法for_each来处理list中的元素
6用STL的通用算法count_if()来统计list中的元素个数
7使用count_if()的一个更加复杂的函数对象。
8使用STL通用算法find()在list中查找对象
9使用STL通用算法find_if()在list中搜索对象
10使用STL通用算法search在list中找一个序列
11使用list的成员函数sort()排序一个list。
12用list的成员函数插入元素到list中
13List构造函数
14使用list成员函数从list中删除元素
15用list成员函数remove()从list中删除元素。
16使用STL通用算法remove()从list中删除元素
17使用STL通用算法stable_partition()和list成员函数splice()来划分一个list
*/
#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
#include <string>
using namespace std;

//assign 函数 参见vector教程
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

//push_back push_front函数
//push_back()把一个对象放到一个list的后面，而 push_front()把对象放到前面
void  push_back_front()
{
	list<string> Milkshakes;
	Milkshakes.push_back("Chocolate");
	Milkshakes.push_back("Strawberry");
	Milkshakes.push_front("Lime");
    Milkshakes.push_front("Vanilla");
	for (auto i : Milkshakes)
		cout << i << " ";
	//输出：Vanilla Lime Chocolate Strawberry
}

//back front函数demo
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
	/*输出结果：
	Entire list:
	Robert 60000
	Linda 75000

	Return from back()
	Linda 75000
	Return from front
	Robert 60000
	*/
}

//begin clear empty end 函数

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
	it = l.end();//end()指向最后一个元素的下一个位置 实际上表示不存在的  不要去end()元素
	it--;
	cout << *it << "  " << endl;
	l.clear();
	cout << "list is :";
	l.empty() ? cout << "null" << endl : cout << "is not null" << endl;
	/*输出：
	list is :null
	list is :is not null
	1
	4
	list is :null
	*/
}

//insert erase size 函数demo
//通用算法remove()使用和list的成员函数不同的方式工作。一般情况下不改变容器的大小。
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
这是find()的一个更强大的版本。这个例子演示了find_if()，它接收一个函数对象的参数作为参数，并使用它来做更复杂的评价对象是否和出的查找条件相付。假设我们的list中有一些按年代排列的包含了事件和日期的记录。我们希望找出发生在1997年的事件。
这是find()的一个更强大的版本。这个例子演示了find_if()，它接收一个函数对象的参数作为参数， 并使用它来做更复杂的评价对象是否和给出的查找条件相付。假设我们的list中有一些按年代排列的包含了事件和日期的记录。我们希望找出发生在1997年的事件。
它在区间[first,end)中搜寻使一元判断式pred为true的第一个元素。
如果没找到，返回end。
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
	//这是程序的输出：
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