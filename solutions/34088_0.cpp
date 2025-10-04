#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 20202;

ll N, A[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for(int i = 0; i < N; i++) cin >> A[i];
    srand(time(NULL));
    int ans = 1;
    vector<ll> factors;
    for(int iter = 0; iter < 100; iter++) {
        int i = rand() % N;
        int j = rand() % N;
        ll n = abs(A[i]-A[j]);
        if(n <= 1) continue;
        factors.clear();
        for(ll k = 2; k * k <= n; k++) {
            if(n%k == 0) factors.push_back(k);
            while(n%k == 0) n/=k;
        }
        if(n > 1) factors.push_back(n);
        for(auto k : factors) {
            int cnt = 0;
            for(int j = 0; j < N; j++) {
                if((A[j]-A[i])%k == 0) cnt++;
            }
            ans = max(ans, cnt);
        }
    }
    cout << ans << "\n";
}