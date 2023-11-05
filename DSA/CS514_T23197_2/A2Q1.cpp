#include<iostream>
#include<stack>
#include<cmath>
using namespace std;

typedef struct pointer{
    double x, y;    
} pointer;

double polar_angle(pointer p2, pointer p1)
{
    return atan2((p2.y - p1.y),(p2.x - p1.x));
}

int orientation(pointer p1, pointer p2, pointer p3)
{
    double slope = ((p3.y - p2.y)*(p2.x - p1.x)) - ((p2.y - p1.y)*(p3.x - p2.x));
    if(slope>0)
        return 1;
    else if(slope<0)
        return -1;
    else
        return 0;
}


void swap(pointer &p1, pointer &p2)
{
    pointer temp=p1;
    p1=p2;
    p2=temp;
}

pointer min_y(pointer *points, int n)
{
    double min = points[0].y;
    int min_loc = 0;
    for(int i=1; i<n; i++)
    {
        if(points[i].y < min)
        {
            min = points[i].y;
            min_loc = i;
        }
    }
    swap(points[min_loc], points[0]);
    return points[0];
}
void merge(pointer *points, int low, int mid, int high, pointer p0)
{
    int i = low, j = mid+1 , k = 0;
    pointer points_b[(high-low+1)];
    while((i<= mid) && (j<= high))
    {
        if(polar_angle(points[i], p0) < polar_angle(points[j], p0))
            points_b[k++] = points[i++];
        else if(polar_angle(points[i], p0) > polar_angle(points[j], p0))
            points_b[k++] = points[j++];
        else
        {
            if(points[j].x >= points[i].x)
                points_b[k++] = points[i++];
            else
                points_b[k++] = points[j++];
            
        }
    }
    while(i <= mid)
    {
        points_b[k++]=points[i++];
    }
    while(j <= high)
    {
        points_b[k++] = points[j++];
    }
    for(k = low; k<=high; k++)
    {
        points[k] = points_b[k - low];
    }
}

void mergesort(pointer *points, int low, int high, pointer p0)
{
    int mid;
    if(low<high)
    {
        mid = (low+high)/2;
        mergesort(points,low, mid, p0);
        mergesort(points,mid+1,high, p0);
        merge(points, low, mid, high, p0);
    }
}

pointer down_top(stack<pointer> s)
{
    pointer top_up = s.top();
    s.pop();
    pointer top_down = s.top();
    s.push(top_up);
    return top_down;
}

void graham_scan(pointer *points, int n)
{
    stack<pointer> s;
    pointer px = min_y(points, n);
    mergesort(points, 1, n-1, px);
    double poler[n+1];

    for(int i = 0; i < n; i++)
        poler[i] = polar_angle(points[i], px);

    for(int i = 1; i < n; i++)
    {
        if(poler[i] == poler[i-1])
        {
            if(points[i].x <= points[i-1].x)
                swap(points[i], points[i-1]);
        }
    }

    // for(int i = 0; i < n; i++)
    // {
    //     cout<<"Point: "<<points[i].x<<", "<<points[i].y<<" px= "<<px.x<<", "<<px.y;
    //     cout<<" Slope: "<<polar_angle(points[i], px)<<endl;
    // }

    s.push(points[0]);
    s.push(points[1]);
    for(int i=2; i<n; i++)
    {
        while((s.size()>=2) && (orientation(down_top(s), s.top(), points[i]) != 1))
        {
            s.pop();
        }
        s.push(points[i]);
    }
    cout<<"Convex Hull Points: "<<endl;
    int count = 0;
    while(!s.empty())
    {
        points[count++] = s.top();
        s.pop();
    }
    for(int i = count-1; i>=0; i--)
        cout<<points[i].x<<" "<<points[i].y<<endl;
    cout<<px.x<<" "<<px.y<<endl;
    cout<<"Total Count: "<<count<<endl;
}

int main()
{
    int n;
    cout<<"Enter Number of Points: ";
    cin>>n;
    if(n==0)
    {
        cout<<"Convex Hull not possible."<<endl;
        return 0;
    }
    cout<<"Enter Points: ";
    pointer points[n];
    for(int i=0; i<n; i++)
        cin>>points[i].x>>points[i].y; 
    graham_scan(points, n);
    return 0;
}