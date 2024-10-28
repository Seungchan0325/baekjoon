#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll p = 1e9 + 7;
const ll x = 375;

int main()
{
    string T, P;
    getline(cin, T);
    getline(cin, P);

    int N = T.size();
    int M = P.size();

    vector<ll> H(N), C(M);
    C[0] = 1;
    for(int i = 1; i < M; i++) {
        C[i] = C[i-1] * x % p;
    }

    for(int i = 0; i < M; i++) {
        H[0] = (x * H[0] + T[i]) % p;
    }
    for(int i = 1; i + M <= N; i++) {
        H[i] = ((H[i-1] - C[M-1]*T[i-1] % p + p) * x % p + T[i+M-1]) % p;
    }
    vector<int> ans;
    ll h = 0;
    for(int i = 0; i < M; i++) {
        h = (x * h + P[i]) % p;
    }

    for(int i = 0; i + M <= N; i++) {
        if(h == H[i]) {
            ans.push_back(i);
        }
    }
    cout << ans.size() << "\n";
    for(auto i : ans) cout << i+1 << " ";
}