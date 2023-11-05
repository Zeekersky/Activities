#include<iostream>
#include"stack.hpp"

using namespace stack_namespace;
int main()
{
int n;
stack<int> s1;
std::cin>> n;
int arr[n];
for(int i = 0; i<n; i++)
{
	std::cin>> arr[i];
}
for(int i =0; i<n; i++)
{
	int flg = 0;
	for(int j=i+1; j<n; j++)
	{
		flg = 1;
		if(arr[i]<arr[j]) {
			s1.push(arr[j]);
			break;
		}
	}
	if(flg == 0)
		s1.push(-1);
	std::cout<<s1.pop()<<std::endl;
}
}
