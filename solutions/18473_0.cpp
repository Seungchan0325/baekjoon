#include <bits/stdc++.h>
#include <queue>

using namespace std;

using ll = long long;

const int MAXN = 303030;

ll n, m, w[MAXN], A[MAXN], B[MAXN], S[MAXN], uf[MAXN];
priority_queue<pair<ll, ll>> pq[MAXN];

int find(int x) {
    if(uf[x] == x) return x;
    return uf[x] = find(uf[x]);
}

void mrg(int x, int y)
{
    x = find(x);
    y = find(y);
    if(x == y) return;
    uf[y] = x;
    w[x] += w[y];
    if(pq[x].size() < pq[y].size()) swap(pq[x], pq[y]);
    while(pq[y].size()) {
        pq[x].push(pq[y].top()); pq[y].pop();
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> w[i];
    for(int i = 1; i <= m; i++) cin >> A[i] >> B[i] >> S[i];
    for(int i = 1; i <= n; i++) uf[i] = i;
    priority_queue<int> q;
    for(int i = 1; i <= m; i++) {
        pq[A[i]].push({-0, i});
        pq[B[i]].push({-0, i});
        if(w[find(A[i])]+w[find(B[i])] >= S[i]) q.push(-i);
    }
    vector<int> ans;
    while(q.size()) {
        auto i = -q.top(); q.pop();
        if(find(A[i]) == find(B[i])) continue;
        ans.push_back(i);
        mrg(A[i], B[i]);
        int now = find(A[i]);
        while(pq[now].size() && -pq[now].top().first <= w[now]) {
            int j = pq[now].top().second; pq[now].pop();
            if(find(A[j]) == find(B[j])) continue;
            A[j] = find(A[j]);
            B[j] = find(B[j]);
            if(w[A[j]] + w[B[j]] >= S[j]) q.push(-j);
            else {
                ll remains = (S[j] - w[A[j]] - w[B[j]] + 1) / 2;
                pq[A[j]].push({-w[A[j]]-remains, j});
                pq[B[j]].push({-w[B[j]]-remains, j});
            }
        }
    }
    cout << ans.size() << "\n";
    for(auto i : ans) cout << i << " ";
}
