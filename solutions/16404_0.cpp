#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, m, S[MAXN], E[MAXN], lazy[4*MAXN], tree[4*MAXN];
vector<int> adj[MAXN];

int cnt = 0;
void dfs(int node, int parent) {
    S[node] = cnt++;
    for(auto next : adj[node])
        if(next != parent)
            dfs(next, node);
    E[node] = cnt - 1;
}

void propagate(int start, int end, int index) {
    if(lazy[index]) {
        tree[index] += (end - start + 1) * lazy[index];
        if(start != end) {
            lazy[2*index] += lazy[index];
            lazy[2*index+1] += lazy[index];
        }
        lazy[index] = 0;
    }
}

void update(int start, int end, int index, int left, int right, int delta) {
    propagate(start, end, index);
    if(end < left || right < start) return;

    if(left <= start && end <= right) {
        tree[index] += (end - start + 1) * delta;
        if(start != end) {
            lazy[2*index] += delta;
            lazy[2*index+1] += delta;
        }
        return;
    }

    int mid = (start + end) / 2;
    update(start, mid, 2*index, left, right, delta);
    update(mid+1, end, 2*index+1, left, right, delta);
    tree[index] = tree[2*index] + tree[2*index+1];
}

int query(int start, int end, int index, int pos) {
    propagate(start, end, index);
    if(end < pos || pos < start) return 0;
    if(start == end) return tree[index];

    int mid = (start + end) / 2;
    return query(start, mid, 2*index, pos) + query(mid+1, end, 2*index+1, pos);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        int p; cin >> p;
        if(p == -1) continue;
        adj[p].push_back(i);
    }

    dfs(1, 0);

    while(m--) {
        int type; cin >> type;
        if(type == 1) {
            int i, w; cin >> i >> w;
            update(0, n-1, 1, S[i], E[i], w);
        } else {
            int i; cin >> i;
            int result = query(0, n-1, 1, S[i]);
            cout << result << "\n";
        }
    }
}