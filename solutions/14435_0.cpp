#include <bits/stdc++.h>
#include <queue>

using namespace std;

#define int long long

const int MAXN = 202020;

bool chk[MAXN];
int N, M, K, Q, L[MAXN], G[MAXN], I[MAXN], J[MAXN], P[MAXN], W[MAXN], num, acc, pp = 1e9, p = 1e9;
priority_queue<pair<int, int>> pq[MAXN];

signed main()
{
    cin >> N >> M >> K >> Q;
    for(int i = 1; i <= M; i++) cin >> L[i];
    for(int i = 1; i <= K; i++) cin >> G[i];
    for(int i = 1; i <= Q; i++) cin >> I[i] >> J[i] >> P[i];

    for(int i = 1; i <= Q; i++) {
        pq[I[i]].push({-1, i});
        pq[J[i]].push({-1, i});
    }

    for(int i = 1; i <= K; i++) {
        W[G[i]]++;
        if(pp < p) W[G[i]]++;
        while(pq[G[i]].size() && -pq[G[i]].top().first <= W[G[i]]) {
            int j = pq[G[i]].top().second; pq[G[i]].pop();
            if(chk[j]) continue;
            if(W[I[j]] + W[J[j]] >= L[P[j]]) {
                chk[j] = true;
                num++;
            } else {
                int remains = (L[P[j]] - W[I[j]] - W[J[j]] + 1) / 2;
                pq[I[j]].push({-W[I[j]]-remains, j});
                pq[J[j]].push({-W[J[j]]-remains, j});
            }
        }
        num += acc;
        cout << num << "\n";
        pp = p;
        p = num;
    }
}
