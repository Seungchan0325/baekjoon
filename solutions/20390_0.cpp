#include <bits/stdc++.h>

using namespace std;

using i128 = __int128_t;
using i64 = long long;

const int MAXN = 10101;

bool vst[MAXN];
i64 N, A, B, C, D, X[MAXN], Xi[MAXN], Xj[MAXN], W[MAXN];

i64 dist(int i, int j)
{
    if(i > j) swap(i, j);
    if(Xi[i] + Xj[j] >= C) return (Xi[i]+Xj[j]-C)^D;
    else return (Xi[i] + Xj[j])^D;
}

void print(i128 x)
{
    if(x == 0) {
        cout << "0";
        return;
    }
    if(x/10 > 0) print(x/10);
    cout << (int)(x%10);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    cin >> A >> B >> C >> D;
    for(int i = 0; i < N; i++) {
        cin >> X[i];
        Xi[i] = ((i128)X[i] * A) % C;
        Xj[i] = ((i128)X[i] * B) % C;
    }
    for(int i = 0; i < N; i++) W[i] = numeric_limits<i64>::max();

    int u = 0;
    i128 ans = 0;
    for(int i = 1; i < N; i++) {
        vst[u] = true;
        i64 mn = numeric_limits<i64>::max();
        int nxt = -1;
        for(int v = 0; v < N; v++) {
            if(vst[v]) continue;
            W[v] = min<i64>(dist(u, v), W[v]);
            if(W[v] < mn) {
                mn = W[v];
                nxt = v;
            }
        }
        ans += mn;
        u = nxt;
    }
    print(ans);
}