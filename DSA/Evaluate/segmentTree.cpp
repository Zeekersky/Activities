#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000; // Maximum size of the input array

struct Node
{
    int value;
    int lazy; // Lazy update value
};

Node tree[4 * MAXN];

void build(int arr[], int index, int left, int right)
{
    if (left == right)
    {
        tree[index].value = arr[left];
        return;
    }
    int mid = (left + right) / 2;
    build(arr, 2 * index + 1, left, mid);
    build(arr, 2 * index + 2, mid + 1, right);
    tree[index].value = tree[2 * index + 1].value + tree[2 * index + 2].value;
}

void lazyUpdate(int index, int left, int right)
{
    if (tree[index].lazy != 0)
    {
        tree[index].value += (right - left + 1) * tree[index].lazy;
        if (left != right)
        {
            tree[2 * index + 1].lazy += tree[index].lazy;
            tree[2 * index + 2].lazy += tree[index].lazy;
        }
        tree[index].lazy = 0;
    }
}

void increment(int index, int left, int right, int ql, int qr, int value)
{
    lazyUpdate(index, left, right);

    if (ql > right || qr < left)
    {
        return;
    }

    if (ql <= left && qr >= right)
    {
        tree[index].lazy += value;
        lazyUpdate(index, left, right);
        return;
    }

    int mid = (left + right) / 2;
    increment(2 * index + 1, left, mid, ql, qr, value);
    increment(2 * index + 2, mid + 1, right, ql, qr, value);
    tree[index].value = tree[2 * index + 1].value + tree[2 * index + 2].value;
}

int query(int index, int left, int right, int ql, int qr)
{
    lazyUpdate(index, left, right);

    if (ql > right || qr < left)
    {
        return 0;
    }

    if (ql <= left && qr >= right)
    {
        return tree[index].value;
    }

    int mid = (left + right) / 2;
    int leftSum = query(2 * index + 1, left, mid, ql, qr);
    int rightSum = query(2 * index + 2, mid + 1, right, ql, qr);
    return leftSum + rightSum;
}

int main()
{
    int N, K;
    cin >> N >> K;
    int seq[MAXN];
    for (int i = 0; i < N; i++)
    {
        cin >> seq[i];
    }
    build(seq, 0, 0, N - 1);

    for (int i = 0; i < K; ++i)
    {
        char command;
        cin >> command;
        if (command == 'U')
        {
            int position, newValue;
            cin >> position >> newValue;
            increment(0, 0, N - 1, position - 1, position - 1, newValue - seq[position - 1]);
            seq[position - 1] = newValue;
        }
        else if (command == 'I')
        {
            int left, right, addValue;
            cin >> left >> right >> addValue;
            increment(0, 0, N - 1, left - 1, right - 1, addValue);
        }
        else if (command == 'G')
        {
            int left, right;
            cin >> left >> right;
            int result = query(0, 0, N - 1, left - 1, right - 1);
            cout << result << endl;
        }
    }

    return 0;
}