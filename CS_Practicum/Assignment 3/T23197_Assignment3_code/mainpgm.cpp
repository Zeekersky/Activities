#include<iostream>
#include"list.hpp"
#include"stack.hpp"
#include"queue.hpp"
using namespace std;
using namespace list_namespace;
using namespace stack_namespace;
using namespace queue_namespace;
int main()
{

list<int> ls;
queue<int> q1;
stack<int> s1;
for(int i=0;i<=10;i++)
{
ls.append(i);
}

cout<<ls.length()<<endl;
ls.remove(5);
ls.remove(6);
cout<<ls.length()<<endl;

s1.push(1);
s1.push(2);
cout<<s1.pop()<<endl;
cout<<s1.pop()<<endl;
cout<<s1.size()<<endl;

q1.push(1);
q1.push(2);
cout<<q1.pop()<<endl;
cout<<q1.pop()<<endl;
cout<<q1.size()<<endl;
}
