#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

int n, thresold_reached = 0;
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


int partition(int a[], int low, int high)
{
    int i = low, j = high + 1, pivot;
    static int random = 0;
    srand(time(NULL));
    int pivot_loc = low + (rand() % (high - low +1));
    pivot = a[pivot_loc];
    swap(&a[pivot_loc], &a[low]);
    do
    {
        do
        {
            i++;
        } while(a[i]<pivot);

        do
        {
            j--;
        } while(a[j]>pivot);
        
        
        if(i<j)
            swap(&a[i], &a[j]);
    }
    while(i<j);
    swap(&a[low], &a[j]);
    return j;
}


void quicksort(int a[], int low, int high)
{
    int j;
    static int subprob_count = 1;
    if(low<high)
    {
        printf("%d ", subprob_count);
        if (subprob_count > ceil(2 * log2(n)))
            thresold_reached++;

        j = partition(a, low, high);
        subprob_count++;
        if((j-low) < (high - j))
        {
            quicksort(a, low, j-1);
            quicksort(a, j+1, high); 
        }
        else
        {
            quicksort(a, j+1, high);
            quicksort(a, low, j-1);
        }
        subprob_count--;
    
    }
}


int main()
{
    int a[100], i;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);

    
    quicksort(a, 0, n-1);
    printf("\n");
    for(i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n%d ", thresold_reached);
    return 0;
}