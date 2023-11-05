#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
int n;

int medianOfMedian(int a[], int low, int high)
{
    if (low == high)
        return a[low];

    int nSize = high - low + 1;
    int numSubGroups = (nSize + 4) / 5;
    int mediansOfSubGroups[numSubGroups];
    cout << "SubGroup Number: " << numSubGroups << " ";
    for (int i = 0; i < numSubGroups; i++)
    {
        int lowSubGroup = low + i * 5;
        int highSubGroup = min(lowSubGroup + 4, high);
        sort(a + lowSubGroup, a + highSubGroup + 1);
        mediansOfSubGroups[i] = a[lowSubGroup + (highSubGroup - lowSubGroup) / 2];
        cout << "Median: " << mediansOfSubGroups[i] << " ";
    }
    return medianOfMedian(mediansOfSubGroups, 0, numSubGroups - 1);
}

int partition(int a[], int low, int high)
{
    int i = low, j = high + 1, pivot_loc;
    int pivot = medianOfMedian(a, low, high);

    for (int t = low; t <= high; t++)
    {
        if (a[t] == pivot)
        {
            pivot_loc = t;
            break;
        }
    }

    cout << "Loc: " << pivot_loc << " Pivot: " << pivot << " "
         << "Range: " << low << " - " << high << " ";
    swap(a[pivot_loc], a[low]);

    do
    {
        do
        {
            i++;
        } while (a[i] < pivot);

        do
        {
            j--;
        } while (a[j] > pivot);

        if (i < j)
            swap(a[i], a[j]);
    } while ((i < j) && (i < ceil(high / 2)) && (j > floor(high / 2)));

    swap(a[low], a[j]);

    cout << "Iteration: ";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;

    return j;
}

int quickselect(int a[], int low, int high, int k)
{
    if (low <= high)
    {

        int j = partition(a, low, high);

        cout << j << "th Smallest: " << endl;

        if (j == k)
            cout << k << "th Smallest: " << a[k];
        else if (j > k)
            quickselect(a, low, j - 1, k);
        else
            quickselect(a, j + 1, high, k);
    }
}

int main()
{
    // int n;
    int k, m;
    cin >> n;
    cin >> k;
    cin >> m;
    int arr[n];
    int p;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    if (k < n)
    {
        // cout << "Kth Smallest: " <<
        quickselect(arr, 0, n - 1, n - k);
        cout << ", Part Sort: ";
        for (int i = 0; i < n; i++)
            cout << arr[i] << " ";
    }
    else
        cout << "Invalid K ";
}