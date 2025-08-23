#include <bits/stdc++.h>

using namespace std;

using i128 = __int128_t;
using i64 = long long;

const int MAXN = 1010101;

i64 mul(i64 x, i64 y, i64 mod)
{
    return (i128)x*y%mod;
}

i64 pow(i64 x, i64 n, i64 mod)
{
    i64 ans = 1;
    while(n) {
        if(n&1) ans = mul(ans, x, mod);
        x = mul(x, x, mod);
        n>>=1;
    }
    return ans;
}

bool miller(i64 n, i64 a)
{
    if(n%a == 0) return false;
    i64 k = n-1;
    while(true) {
        i64 v = pow(a, k, n);
        if(k&1) return (v != 1 && v != n-1);
        else if(v == n-1) return false;
        k>>=1;
    }
}

bool isprime(i64 n)
{
    for(i64 a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if(n == a) return true;
        if(n > 40 && miller(n, a)) return false;
    }
    if(n <= 40) return false;
    return true;
}

void factorize(i64 n, map<i64, int>& v)
{
    if(n == 1) return;
    if(~n&1) {
        v[2]++;
        factorize(n/2, v);
        return;
    }
    if(isprime(n)) {
        v[n]++;
        return;
    }
    i64 a, b, c, g = n;
    auto f = [&](i64 x) {
        return (c + (i128)x * x) % n;
    };
    do {
        if(g == n) {
            a = b = rand() % (n-2) + 2;
            c = rand() % 20 + 1;
        }
        a = f(a);
        b = f(f(b));
        g = gcd(a-b, n);
    } while(g == 1);
    factorize(g, v);
    factorize(n/g, v);
}

int dimension;
i64 N, M, A[MAXN], B[1501010], S[1501010], stride[20];
map<i64, int> factors;
vector<i64> p;
vector<int> sz;

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> A[i]; A[i] += A[i-1];
    }
    M = A[N];

    factorize(M, factors);
    dimension = factors.size();
    for(auto& [key, item] : factors) p.push_back(key), sz.push_back(item+1);
    i64 tot = 1;
    for(int i = 0; i < dimension; i++)  {
        stride[i] = tot;
        tot *= sz[i];
    }
    stride[dimension] = tot;
    assert(tot < 1501010);

    for(int i = 1; i < N; i++) {
        i64 x = gcd(M, A[i]);
        int idx = 0;
        for(int j = 0; j < dimension; j++) {
            int cnt = 0;
            while(x%p[j] == 0) {
                x /= p[j];
                cnt++;
            }
            idx += stride[j] * (sz[j]-cnt-1);
        }
        B[idx]++;
        S[idx]++;
    }

    for(int i = 0; i < dimension; i++) {
        int r = 0;
        for(int j = 0; j < tot; j++) {
            if(j%stride[i+1] == 0) r = j;
            if(j-stride[i] < r) continue;
            S[j] += S[j-stride[i]];
        }
    }

    vector<i64> ans(N);
    for(int i = 0; i < tot; i++) {
        int k = i;
        i64 num = 1;
        for(int j = 0; j < dimension; j++) {
            num *= pow(p[j], sz[j]-k%sz[j]-1, LLONG_MAX);
            k /= sz[j];
        }
        if(gcd(num, M) != num) continue;
        ans[N-S[i]-1] = max(ans[N-S[i]-1], num);
    }
    for(int i = 1; i < N; i++) ans[i] = max(ans[i-1], ans[i]);
    for(int i = 0; i < N; i++) cout << ans[i] << " ";
    cout << "\n";
}