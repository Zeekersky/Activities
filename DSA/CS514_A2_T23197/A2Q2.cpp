#include <iostream>
#include <cmath>
using namespace std;

int findMaxDigit(int *dg, int n)
{
    if (n <= 0)
        return -1;

    int max = dg[0];
    for (int i = 1; i < n; i++)
        if (max < dg[i])
            max = dg[i];
    int count = 0;
    for (; max != 0; count++)
        max = max / 10;
    return count;
}

int reqDigit(int val, int loc2)
{
    while (loc2-- != 1)
        val = val / 10;
    return val % 10;
}

count_sort(int *dg, int loc, int cap)
{
    int count[10];
    int rdSorted[cap];

    for (int i = 0; i < 10; i++)
        count[i] = 0;

    for (int i = 0; i < cap; i++)
        count[reqDigit(dg[i], loc)]++;

    for (int i = 1; i < 10; i++)
        count[i] = count[i] + count[i - 1];

    for (int i = (cap - 1); i >= 0; i--)
        rdSorted[--count[reqDigit(dg[i], loc)]] = dg[i];

    for (int i = 0; i < cap; i++)
        dg[i] = rdSorted[i];
}

radix_sort(int *dg, int n)
{
    int dg_pos[n], dg_neg[n], ipos = 0, ineg = 0;
    for (int i = 0; i < n; i++)
    {
        if (dg[i] >= 0)
            dg_pos[ipos++] = dg[i];
        else
            dg_neg[ineg++] = (-1) * dg[i];
    }
    int nPos = ipos;
    int nNeg = ineg;
    int count_pos = findMaxDigit(dg_pos, nPos);
    int count_neg = findMaxDigit(dg_neg, nNeg);
    if (nPos != 0)
    {
        for (int c = 1; c <= count_pos; c++)
            count_sort(dg_pos, c, nPos);
    }
    if (nNeg != 0)
    {
        for (int c = 1; c <= count_neg; c++)
            count_sort(dg_neg, c, nNeg);
    }

    int iPos = 0, iNeg = 0;
    cout << "Sorted Order: ";
    for (int i = 0; i < n; i++)
    {
        if (i < nNeg)
        {
            dg[i] = (-1) * dg_neg[nNeg - iNeg - 1];
            iNeg++;
        }
        else if ((i < (nPos + nNeg)) && (i >= nNeg))
            dg[i] = dg_pos[iPos++];
        cout << dg[i] << " ";
    }
}

int main()
{
    int n;
    cout << "Enter Number of Components: ";
    cin >> n;
    int dg[n];
    cout << "Enter Components: ";
    for (int i = 0; i < n; i++)
        cin >> dg[i];
    radix_sort(dg, n);
}