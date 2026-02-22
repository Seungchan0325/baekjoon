#include <bits/stdc++.h>

using namespace std;

#define int long long

using ll = long long;

const int MAXN = 2010;
const int MAXL = 2010;

// p/q
struct Frac {
    ll p, q;
    Frac(ll _p = 0, ll _q = 1) : p(_p), q(_q) {
        assert(q != 0);
        if(q < 0) {
            p = -p;
            q = -q;
        }
    }

    Frac operator + (const Frac& rhs) const {
        ll m = p * rhs.q + rhs.p * q;
        ll n = q * rhs.q;
        return Frac(m, n);
    }

    Frac operator - (const Frac& rhs) const {
        ll m = p * rhs.q - rhs.p * q;
        ll n = q * rhs.q;
        return Frac(m, n);
    }    

    Frac operator * (const Frac& rhs) const {
        ll m = p * rhs.p;
        ll n = q * rhs.q;
        return Frac(m, n);
    }

    auto operator <=> (const Frac& rhs) const {
        return (__int128_t)p * rhs.q <=> (__int128_t)rhs.p * q;
    }

    bool operator==(const Frac& rhs) const {
        return (__int128_t)p * rhs.q == (__int128_t)rhs.p * q;
    }

    Frac inv() const {
        return Frac(q, p);
    }
    
    Frac ceil() const {
        return p >= 0 ? Frac((p+q-1)/q) : Frac(p/q);
    }
    
    Frac floor() const {
        return p >= 0 ? Frac(p/q) : Frac((p-q+1)/q);
    }

    ll to_int() const {
        return p / q;
    }
};

bool chk[MAXN];
int N, L, V[MAXN][MAXL], S[MAXN][MAXL];
Frac P[MAXN][MAXN];

signed main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> L;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= L; j++) {
            cin >> V[i][j];
            S[i][j] = S[i][j-1] + V[i][j];
        }
    }

    if(L == 0) {
        for(int i = 0; i < N; i++) {
            cout << "0 1\n";
        }
        for(int i = 1; i <= N; i++) cout << i << " ";
        return 0;
    }

    for(int i = 1; i <= N; i++) {
        int k = 0;
        int sum = 0;
        for(int j = 1; j < N; j++) {
            Frac t(j * S[i][L], N);
            while(sum + V[i][k+1] < t) {
                k++;
                sum += V[i][k];
            }
            t = t - sum;
            P[i][j] = t * Frac(1, V[i][k+1]) + k;
        }
    }

    vector<Frac> X;
    vector<int> p;
    for(int i = N-1; i >= 0; i--) {
        Frac mx(-1, 1);
        int mxi = -1;
        for(int j = 1; j <= N; j++) {
            if(chk[j]) continue;
            if(P[j][i] > mx) {
                mx = P[j][i];
                mxi = j;
            }
        }
        chk[mxi] = true;
        X.push_back(mx);
        p.push_back(mxi);
    }
    reverse(X.begin(), X.end());
    reverse(p.begin(), p.end());
    for(int i = 1; i < N; i++) cout << X[i].p << " " << X[i].q << "\n";
    for(int i = 0; i < N; i++) cout << p[i] << " ";
}