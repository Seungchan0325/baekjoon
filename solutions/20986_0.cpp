#include <bits/stdc++.h>

using namespace std;

struct Fenwick {
    int N;
    vector<int> tree;
    Fenwick(int N) : N(N), tree(N+1) {}

    void upd(int x, int v)
    {
        while(x <= N) {
            tree[x] += v;
            x += x & -x;
        }
    }

    int qry(int x)
    {
        int ret = 0;
        while(x > 0) {
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }
};

const int MAXN = 5050;

int n, h[MAXN], r[MAXN], inv1[MAXN][MAXN], inv2[MAXN][MAXN], dp[MAXN];

// inv1[i][j] = [i, j]에서 count
// inv2[i][j] = [1, i]에서 (i, j]보다 뒤에 있는 개수

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> h[i], r[h[i]] = i;
    for(int i = 1; i <= n; i++) {
        Fenwick f(n);
        int sum = 0;
        for(int j = i; j <= n; j++) {
            inv1[i][j] = inv1[i][j-1] + f.qry(r[j]);
            f.upd(r[j], 1);
        }
    }

    Fenwick f(n);
    for(int i = 1; i <= n; i++) {
        for(int j = i; j <= n; j++) {
            inv2[i][j] = inv2[i][j-1] + f.qry(n) - f.qry(r[j]);
        }
        f.upd(r[i], 1);
    }

    for(int i = 1; i <= n; i++) {
        dp[i] = 1e9;
        int sum = 0;
        for(int j = 1; j <= i; j++) {
            dp[i] = min(dp[i], dp[j-1] + inv1[j][i] + inv2[j][i]);
        }
    }

    cout << dp[n] << "\n";
}