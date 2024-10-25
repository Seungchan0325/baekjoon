#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll P1 = 523;
const ll M1 = 1e9 + 7;
const ll P2 = 325;
const ll M2 = 1e9 + 9;

const int MAXN = 400005;

ll N, K, H1[MAXN], H2[MAXN], A[MAXN], RA[MAXN], pw1[MAXN], pw2[MAXN];

pair<ll, ll> Hash(int i, int len)
{
    ll h1 = (H1[i+len] - pw1[len] * H1[i] % M1 + M1) % M1;
    ll h2 = (H2[i+len] - pw2[len] * H2[i] % M2 + M2) % M2;
    return {h1, h2};
}

struct cmp {
    bool operator () (int i, int j)
    {
        int lo = 0;
        int hi = N;
        while(lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            if(Hash(i, mid) == Hash(j, mid)) lo = mid;
            else hi = mid;
        }

        return RA[i+hi] < RA[j+hi];
    }
};

int main()
{
    cin >> N >> K;
    for(int i = 1; i <= N; i++) {
        cin >> A[i];
        RA[N-i+1] = RA[N-i+1+N] = A[i];
    }

    pw1[0] = pw2[0] = 1;
    for(int i = 1; i <= 2*N; i++) {
        pw1[i] = pw1[i-1] * P1 % M1;
        pw2[i] = pw2[i-1] * P2 % M2;
    }

    for(int i = 1; i <= 2*N; i++) {
        H1[i] = (H1[i-1] * P1 + RA[i]) % M1;
        H2[i] = (H2[i-1] * P2 + RA[i]) % M2;
    }

    vector<int> v(N-1);
    iota(v.begin(), v.end(), 1);
    sort(v.begin(), v.end(), cmp());
    int k = v[K-1];
    for(int i = 1; i <= N; i++) {
        cout << RA[k+i] << " ";
    }
}