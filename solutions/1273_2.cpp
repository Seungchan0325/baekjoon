#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300005;
const int MAXH = 3e6 + 5;
const int point[] = {1, 2, 5};

int n, m, max_h, cans[3][MAXN], score[MAXH], tree[MAXH];

void update(int i, int num)
{
    i++;
    while(i < max_h)
    {
        tree[i] += num;
        i += (i & -i);
    }
}

int sum(int i)
{
    i++;
    int ret = 0;
    while(i > 0)
    {
        ret += tree[i];
        i -= (i & -i);
    }
    return ret;
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
        score[0] += 1;
        score[cans[0][i]] += -1 + 2;
        score[cans[0][i] + cans[1][i]] += -2 + 5;
        score[cans[0][i] + cans[1][i] + cans[2][i]] -= 5;
        max_h = max(cans[0][i] + cans[1][i] + cans[2][i] + 5, max_h);
    }

    for(int i = 0; i < max_h; i++)
    {
        score[i + 1] += score[i];
        update(i, 1);
    }

    cin >> m;
    while(m--)
    {
        int h;
        cin >> h;

        int lo = 0, hi = max_h;
        while(lo + 1 < hi)
        {
            int mid = (lo + hi) / 2;
            int cnt = sum(mid);
            if(cnt < h) lo = mid;
            else hi = mid;
        }

        update(hi, -1);

        cout << score[hi] << "\n";
    }
}