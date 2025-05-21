#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 1010101;
const int LOGN = 20;

ll T, L, t[MAXN<<1], sparse[MAXN<<1][LOGN+1], l[MAXN];
int N, K;

ll qry(ll tm, ll d)
{
    int i = lower_bound(t+1, t+2*N+1, tm) - t;
    if(t[i] - tm - 1 >= d) return 0;
    if(i > N) i -= N;
    for(int j = LOGN; j >= 0; j--)
        if((i+(1<<j)) < (N<<1) && sparse[i][j] < d)
            i += 1<<j;
    return (t[i] - tm + T) % T;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> T >> N;
    cin >> L >> K;
    for(int i = 1; i <= N; i++) cin >> t[i], t[i+N] = t[i]+T;
    for(int i = 1; i <= K; i++) cin >> l[i];

    memset(sparse, 0x3f, sizeof(sparse));

    ll mx = 0;
    for(int i = 1; i < N<<1; i++) {
        sparse[i][0] = t[i+1] - t[i] - 1;
        mx = max(sparse[i][0], mx);
    }

    for(int j = 1, k = 1; j <= LOGN; j++, k<<=1)
        for(int i = 1; i < N<<1; i++)
            if(i+k < N<<1)
                sparse[i][j] = max(sparse[i][j-1], sparse[i+k][j-1]);

    ll ans = 0;
    for(int i = 1; i < K; i++) {
        if(l[i+1] - l[i] - 1 > mx) {
            cout << "What is that map newbie...\n";
            return 0;
        }

        ans += qry(ans % T, l[i+1] - l[i] - 1);
        ans += l[i+1] - l[i];
    }

    cout << ans << "\n";
}