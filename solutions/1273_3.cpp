#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300005;
const int MAXH = 3e6 + 5;
const int point[] = {1, 2, 5};

int n, m, cans[3][MAXN], score[MAXH+5], tree[4*MAXH];

void update(int start, int end, int index, int pos, int delta)
{
    if(pos < start || end < pos) return;

    if(start == end)
    {
        tree[index] += delta;
        return;
    }

    int mid = (start + end) / 2;
    update(start, mid, 2*index, pos, delta);
    update(mid+1, end, 2*index+1, pos, delta);
    tree[index] = tree[2*index] + tree[2*index+1];
}

int query(int start, int end, int index, int kth)
{
    if(start == end) return start;
    int mid = (start + end) / 2;
    if(kth <= tree[2*index])
    {
        return query(start, mid, 2*index, kth);
    }
    else
    {
        return query(mid+1, end, 2*index+1, kth - tree[2*index]);
    }
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

    int max_h = 0;
    for(int i = 0; i < n; i++)
    {
        int sum = 0;
        for(int j = 0; j < 3; j++)
        {
            sum += cans[j][i];
        }
        max_h = max(max_h, sum);
    }

    for(int i = 0; i < n; i++)
    {
        score[0] += 1;
        score[cans[0][i]] += -1 + 2;
        score[cans[0][i] + cans[1][i]] += -2 + 5;
        score[cans[0][i] + cans[1][i] + cans[2][i]] -= 5;
    }

    for(int i = 0; i < MAXH; i++)
    {
        score[i+1] += score[i];
        update(0, max_h, 1, i, 1);
    }

    cin >> m;
    while(m--)
    {
        int h;
        cin >> h;
        int idx = query(0, max_h, 1, h);
        update(0, max_h, 1, idx, -1);
        cout << score[idx] << "\n";
    }
}