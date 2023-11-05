#include <bits/stdc++.h>
using namespace std;

void build(int arr[], int tree[], int index, int left, int right)
{
    if (left == right)
    {
        tree[index] = arr[left];
        return;
    }
    int mid = (left + right) / 2;
    build(arr, tree, 2 * index + 1, left, mid);
    build(arr, tree, 2 * index + 2, mid + 1, right);
    tree[index] = tree[2 * index + 1] + tree[2 * index + 2];
}

void update(int tree[], int index, int left, int right, int value, int loc)
{
    if (left == right)
    {
        tree[index] = value;
        return;
    }
    int mid = (left + right) / 2;
    if (loc <= mid)
        update(tree, 2 * index + 1, left, mid, value, loc);
    else
        update(tree, 2 * index + 2, mid + 1, right, value, loc);
    tree[index] = tree[2 * index + 1] + tree[2 * index + 2];
}

void increment(int tree[], int index, int left, int right, int ql, int qr, int value)
{
    if (ql > right || qr < left)
        return;
    if (left == right)
    {
        tree[index] += value;
        return;
    }
    int mid = (left + right) / 2;
    increment(tree, 2 * index + 1, left, mid, ql, qr, value);
    increment(tree, 2 * index + 2, mid + 1, right, ql, qr, value);
    tree[index] = tree[2 * index + 1] + tree[2 * index + 2];
}

int query(int tree[], int index, int left, int right, int loc)
{
    if (left == right)
        return tree[index];
    int mid = (left + right) / 2;
    if (loc <= mid)
        return query(tree, 2 * index + 1, left, mid, loc);
    else
        return query(tree, 2 * index + 2, mid + 1, right, loc);
}

int main()
{
    int N, K;
    cin >> N >> K;
    int seq[N], tree[4 * N];
    for (int i = 0; i < N; i++)
        cin >> seq[i];
    build(seq, tree, 0, 0, N - 1);

    for (int i = 0; i < K; ++i)
    {
        char command;
        cin >> command;
        if (command == 'U')
        {
            int position, newValue;
            cin >> position >> newValue;
            update(tree, 0, 0, N - 1, newValue, position - 1);
        }
        else if (command == 'I')
        {
            int left, right, addValue;
            cin >> left >> right >> addValue;
            increment(tree, 0, 0, N - 1, left - 1, right - 1, addValue);
        }
        else if (command == 'G')
        {
            int position;
            cin >> position;
            int result = query(tree, 0, 0, N - 1, position - 1);
            cout << result << endl;
        }
    }

    return 0;
}
