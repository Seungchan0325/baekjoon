#include <bits/stdc++.h>
#include <queue>

using namespace std;

using ll = long long;

const int MAXN = 505050;

struct Node {
    ll p, x, i;
    bool operator < (const Node& t) const {
        return p * t.x < t.p * x;
    }
    bool operator == (const Node& t) const {
        return p == t.p && x == t.x;
    }
};

ll N, M, A[MAXN], B[MAXN], uf[MAXN<<1];
Node nd[MAXN<<1];

int find(int x)
{
    if(uf[x] == x) return x;
    return uf[x] = find(uf[x]);
}

void mrg(int x, int y)
{
    x = find(x);
    y = find(y);
    if(x == y) return;
    uf[y] = x;
    nd[x].p += nd[y].p;
    nd[x].x += nd[y].x;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M; N--; M--;
    for(int i = 0; i <= N; i++) cin >> A[i];
    for(int i = 0; i <= M; i++) cin >> B[i];
    ll ans = M * A[N] + N * B[M];
    priority_queue<Node> pq;
    for(int i = 1; i <= N; i++) {
        uf[i] = i;
        nd[i].i = i;
        nd[i].p = A[i-1] - A[i];
        nd[i].x = 1;
        ans -= nd[i].p * (i-1);
        pq.push(nd[i]);
    }
    for(int i = 1; i <= M; i++) {
        uf[i+N] = i+N;
        nd[i+N].i = i+N;
        nd[i+N].p = B[i-1] - B[i];
        nd[i+N].x = 1;
        ans -= nd[i+N].p * (i-1);
        pq.push(nd[i+N]);
    }
    while(!pq.empty()) {
        auto t = pq.top(); pq.pop();
        if(find(t.i) != t.i || nd[t.i] != t) continue;
        if(t.i == 1 || t.i == 1+N) {
            ans += t.p*nd[0].x;
            mrg(0, t.i);
        } else {
            ans += t.p*nd[find(t.i-1)].x;
            mrg(t.i-1, t.i);
            int j = find(t.i);
            if(j > 0)
                pq.push(nd[j]);
        }
    }
    cout << ans << "\n";
}
