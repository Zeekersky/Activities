#include<iostream>
#include<fstream>
#include"queue.hpp"

using namespace std;
using namespace queue_namespace;

int main()
{
queue<char> que;
std::string st;
std::ifstream file; 
std::ofstream file1("output.txt");

file.open ("input.txt");
file>>st;
int b = int(st[0])-48;
// remaining integers are in queue
for(int i = 0; i<st.length(); i++)
{
que.push(st[i]);
}

// rotate the integers by b position 
for (int i= 1; i<= b; i++)
{
char elem = que.pop();
que.push(elem);
}

for(int i=0; i<st.length(); i++)
{
file1.put(que.pop());
}

}
