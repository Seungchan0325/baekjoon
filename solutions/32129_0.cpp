#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 505050;
const ll inf = 1e18;

ll N, Q, V[MAXN], PM[MAXN], PS[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> Q;
    for(int i = 1; i <= N; i++) {
        cin >> V[i];
        PS[i] = PS[i-1] + V[i];
        PM[i] = max(PM[i-1], V[i]+i-1);
    }
    V[N+1] = inf;
    auto compute = [&](ll x) -> ll {
        return x * (PM[x] + PM[x] - x + 1) / 2 - PS[x];
    };
    ll sum = 0;
    while(Q--) {
        int op; cin >> op;
        if(op == 1) {
            int x; cin >> x;
            sum += x;
        } else {
            int lo = 1;
            int hi = N+1;
            while(lo + 1 < hi) {
                int mid = (lo + hi) / 2;
                if(compute(mid) <= sum) lo = mid;
                else hi = mid;
            }

            if(PM[lo]-lo+1 <= V[lo+1]) {
                cout << PM[lo] + (sum - compute(lo)) / lo << "\n";
            } else {
                cout << PM[lo] << "\n";
            }
        }
    }
}