#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10000;

int n, k, m, tree[MAXN + 1];

void update(int idx, int delta)
{
    while(idx <= MAXN) {
        tree[idx] += delta;
        idx += (idx & -idx);
    }
}

int query(int idx)
{
    int ret = 0;
    while(0 < idx) {
        ret += tree[idx];
        idx -= (idx & -idx);
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    while(true) {
        cin >> n >> k >> m;
        if(n == 0 && k == 0 && m == 0) break;

        for(int i = 1; i <= n; i++) {
            tree[i] = (i & -i);
        }

        int nth = m - 1;
        for(int i = 1; i < n; i++) {
            int lo = 0, hi = n;
            while(lo + 1 < hi) {
                int mid = (lo + hi) / 2;
                if(query(mid) < nth + 1) lo = mid;
                else hi = mid;
            }
            update(hi, -1);
            nth = (nth + k - 1) % (n - i);
        }

        int lo = 0, hi = n;
        while(lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            if(query(mid) < 1) lo = mid;
            else hi = mid;
        }
        cout << hi << "\n";
    }
}