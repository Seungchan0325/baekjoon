#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010101;
const int MAXM = 20;
const int mod = 1e9 + 7;

int N, M, F[1<<MAXM], pw[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;
    for(int i = 1; i <= N; i++) {
        int k; cin >> k;
        int x = 0;
        for(int i = 0; i < k; i++) {
            int toy; cin >> toy; toy--;
            x |= 1<<toy;
        }
        F[x]++;
    }

    for(int i = 0; i < M; i++)
        for(int x = 0; x < 1<<M; x++)
            if(x&(1<<i)) F[x] = F[x]+F[x^(1<<i)];

    pw[0] = 1;
    for(int i = 1; i <= N; i++) pw[i] = (pw[i-1]+pw[i-1])%mod;

    unsigned full = (1<<M)-1;
    long long ans = pw[N];
    for(unsigned x = 0; x < full; x++) {
        if(popcount(full&~x)&1) ans -= pw[F[x]];
        else ans += pw[F[x]];
        if(ans >= mod) ans -= mod;
        else if(ans < 0) ans += mod;
    }
    cout << ans << "\n";
}