#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2")

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 7070;
const int mod = 1e9 + 7;

int N, X1[MAXN], Y1[MAXN], X2[MAXN], Y2[MAXN], d[MAXN][MAXN];
bitset<MAXN> adj[MAXN];

void bfs(int s)
{
    bitset<MAXN> vst;
    for(int i = 0; i < N; i++) vst[i] = 1;
    queue<int> q;
    q.push(s);
    vst[s] = 0;
    d[s][s] = 0;
    while(!q.empty()) {
        int now = q.front(); q.pop();
        auto nxts = adj[now]&vst;
        for(int nxt = nxts._Find_first(); nxt < MAXN; nxt = nxts._Find_next(nxt)) {
            vst[nxt] = 0;
            d[s][nxt] = d[s][now] + 1;
            q.push(nxt);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 0; i < N; i++) {
        cin >> X1[i] >> Y1[i] >> X2[i] >> Y2[i];
        if(X1[i] > X2[i]) swap(X1[i], X2[i]);
        if(Y1[i] > Y2[i]) swap(Y1[i], Y2[i]);
    }

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(i == j) continue;
            if((X1[i] == X2[i]) == (X1[j] == X2[j])) continue;
            if(X1[i] <= X1[j] && X2[j] <= X2[i] && Y1[j] <= Y1[i] && Y2[i] <= Y2[j] ||
               X1[j] <= X1[i] && X2[i] <= X2[j] && Y1[i] <= Y1[j] && Y2[j] <= Y2[i]) adj[i][j] = 1;
        }
    }

    for(int i = 0; i < N; i++) bfs(i);
    ll ans = 0;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            ans = (ans + ((ll)d[i][j] * (i+1) * (j+1)) % mod) % mod;
        }
    }
    cout << ans << "\n";
}