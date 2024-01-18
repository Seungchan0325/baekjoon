#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, k, tree[4*MAXN];

void build(int start = 0, int end = n - 1, int index = 1)
{
    if(start == end)
    {
        tree[index] = 1;
        return;
    }

    int mid = (start + end) / 2;
    build(start, mid, 2*index);
    build(mid+1, end, 2*index+1);
    tree[index] = tree[2*index] + tree[2*index+1];
}

void update(int pos, int delta, int start = 0, int end = n - 1, int index = 1)
{
    if(end < pos || pos < start) 
    {
        return;
    }

    if(start == end)
    {
        tree[index] += delta;
        return;
    }

    int mid = (start + end) / 2;
    update(pos, delta, start, mid, 2*index);
    update(pos, delta, mid+1, end, 2*index+1);
    tree[index] = tree[2*index] + tree[2*index+1];
}

int query(int target, int start = 0, int end = n - 1, int index = 1)
{
    if(start == end)
    {
        return start;
    }

    int l = tree[2*index];
    int r = tree[2*index+1];
    int mid = (start + end) / 2;

    if(target <= l)
    {
        return query(target, start, mid, 2*index);
    }
    else
    {
        return query(target - l, mid+1, end, 2*index+1);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    build();

    int target = 0;
    cout << "<";
    for(int remain = n; remain > 0; remain--)
    {
        target = (target + k - 1 + remain) % remain;

        int ans = query(target + 1);
        update(ans, -1);

        cout << ans + 1;
        if(remain != 1)
        {
            cout << ", ";
        }
    }
    cout << ">\n";
}