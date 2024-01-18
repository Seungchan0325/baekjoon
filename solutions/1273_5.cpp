#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300005;
const int MAXH = 3e6 + 5;
const int point[] = {1, 2, 5};

int n, m, cans[3][MAXN], cans_tree[4*MAXH], cans_lazy[4*MAXH], cnt_tree[4*MAXH];

void update(int start, int end, int index, int pos, int delta)
{
    if(pos < start || end < pos) return;

    if(start == end)
    {
        cnt_tree[index] += delta;
        return;
    }

    int mid = (start + end) / 2;
    update(start, mid, 2*index, pos, delta);
    update(mid+1, end, 2*index+1, pos, delta);
    cnt_tree[index] = cnt_tree[2*index] + cnt_tree[2*index+1];
}

int query(int start, int end, int index, int kth)
{
    if(start == end) return start;
    int mid = (start + end) / 2;
    if(kth <= cnt_tree[2*index])
    {
        return query(start, mid, 2*index, kth);
    }
    else
    {
        return query(mid+1, end, 2*index+1, kth - cnt_tree[2*index]);
    }
}

void propagate(int start, int end, int index)
{
    cans_tree[index] += (end - start + 1) * cans_lazy[index];
    if(start != end)
    {
        cans_lazy[2*index] += cans_lazy[index];
        cans_lazy[2*index+1] += cans_lazy[index];
    }
    cans_lazy[index] = 0;
}

void update_range(int start, int end, int index, int left, int right, int delta)
{
    propagate(start, end, index);
    if(right < start || end < left) return;

    if(left <= start && end <= right)
    {
        cans_tree[index] += (end - start + 1) * delta;
        if(start != end)
        {
            cans_lazy[2*index] += delta;
            cans_lazy[2*index+1] += delta;
        }
        return;
    }

    int mid = (start + end) / 2;
    update_range(start, mid, 2*index, left, right, delta);
    update_range(mid+1, end, 2*index+1, left, right, delta);
    cans_tree[index] = cans_tree[2*index] + cans_tree[2*index+1];
}

int query_range(int start, int end, int index, int left, int right)
{
    propagate(start, end, index);
    if(right < start || end < left) return 0;

    if(left <= start && end <= right) return cans_tree[index];

    int mid = (start + end) / 2;
    return query_range(start, mid, 2*index, left, right) + query_range(mid+1, end, 2*index+1, left, right);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cin >> cans[i][j];
        }
    }

    for(int i = 0; i < n; i++)
    {
        int sum = 0;
        for(int j = 0; j < 3; j++)
        {
            update_range(0, MAXH - 1, 1, sum, sum + cans[j][i] - 1, point[j]);
            sum += cans[j][i];
        }
    }

    for(int i = 0; i < MAXH; i++)
    {
        update(0, MAXH - 1, 1, i, 1);
    }

    cin >> m;
    while(m--)
    {
        int h;
        cin >> h;
        int idx = query(0, MAXH - 1, 1, h);
        update(0, MAXH - 1, 1, idx, -1);
        int result = query_range(0, MAXH - 1, 1, idx, idx);
        update_range(0, MAXH - 1, 1, idx, idx, -result);
        cout << result << "\n";
    }
}