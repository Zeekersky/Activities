#include<iostream>
#include<cmath>
using namespace std;

int findMaxDigit(int *dg, int n)
{
    int max = dg[0];
    for(int i = 1; i<n; i++)
        if(max<dg[i])
            max = dg[i];
    int count = 0;
    for(; max!=0; count++)
        max = max / 10;
    return count;
}

int reqDigit(int val, int loc2)
{
    while(loc2-- !=1)
        val = val/10;
    return val%10;
}

count_sort(int *dg, int loc, int cap)
{
    int count[10];
    int rdSorted[cap];

    for(int i = 0; i < 10; i++)
        count[i] = 0;

    for(int i = 0; i < cap; i++)
        count[reqDigit(dg[i], loc)]++;
    
    for(int i = 1; i < 10; i++)
        count[i] = count[i] + count[i-1];

    // for(int i = 0; i<10; i++)
    //     cout<<"count: "<<count[i]<<", ";
    // cout<<endl;
    
    for(int i = (cap-1); i>=0; i--)
        rdSorted[--count[reqDigit(dg[i], loc)]] = dg[i];

    for(int i = 0; i < cap; i++)
        dg[i] = rdSorted[i];
}

radix_sort(int *dg, int n)
{
    int count = findMaxDigit(dg, n);
    for(int c = 1; c <= count; c++)
        count_sort(dg, c, n);
    cout<<"Sorted Order: ";
    for(int i = 0; i < n; i++)
        cout<<dg[i]<<" ";
}

int main()
{
    int n;
    cout<<"Enter Number of Components: ";
    cin>>n;
    int dg[n];
    cout<<"Enter Components: ";
    for(int i = 0; i < n; i++)
        cin>>dg[i];
    radix_sort(dg, n);
}