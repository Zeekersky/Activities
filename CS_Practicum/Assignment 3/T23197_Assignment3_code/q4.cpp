#include<iostream>
#include"list.hpp"
#include"queue.hpp"

using namespace std;
using namespace list_namespace;
using namespace queue_namespace;

int main()
{
int n;
queue<string> q1;
std::cout<<"Enter range: "<<std::endl;
std::cin>>n;
q1.push("1");
for(int i = 0; i<n; i++)
{
string st = q1.front();
q1.pop();
std::cout<<st<<std::endl;
q1.push(st+"0");
q1.push(st+"1");
}
return 0;
}
