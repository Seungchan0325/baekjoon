#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 100005;

int N, D;
ll T[MAXN], V[MAXN];

ll DnC(int s, int e, int optL, int optR)
{
    if(e < s) return -1;

    int m = (s + e) / 2;
    ll opt = -1;
    int optI = -1;
    for(int j = max(m, optL); j <= min(m+D, optR); j++) {
        ll cand = (j - m) * T[j] + V[m];
        if(cand > opt) {
            opt = cand;
            optI = j;
        }
    }

    opt = max(opt, DnC(s, m-1, optL, optI));
    opt = max(opt, DnC(m+1, e, optI, optR));
    return opt;
}

int main()
{
    cin >> N >> D;
    for(int i = 1; i <= N; i++) cin >> T[i];
    for(int i = 1; i <= N; i++) cin >> V[i];

    ll result = DnC(1, N, 1, N);
    cout << result;
}