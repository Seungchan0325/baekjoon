#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXL = 80005;
const int MAXG = 805;

ll L, G, C[MAXL];
ll DP[MAXG][MAXL], sum[MAXL];

ll Cost(int i, int j)
{
    return (j - i + 1) * (sum[j] - sum[i-1]);
}

void DnC(int k, int s, int e, int l, int r)
{
    if(s > e) return;
    int m = (s + e) / 2;

    ll res = 1e18;
    ll mni = -1;
    for(int i = l; i <= min(m, r); i++) {
        ll cand = DP[k-1][i-1] + Cost(i, m);

        if(cand < res) {
            res = cand;
            mni = i;
        }
    }

    DP[k][m] = res;

    DnC(k, s, m - 1, l, mni);
    DnC(k, m+1, e, mni, r);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> L >> G;
    G = min(L, G);
    for(int i = 1; i <= L; i++) {
        cin >> C[i];
        sum[i] += sum[i-1] + C[i];
    }

    memset(DP, 0x7F, sizeof(DP));
    DP[0][0] = 0;
    for(int k = 1; k <= G; k++) {
        DnC(k, 1, L, 1, L);
    }

    cout << DP[G][L];
}