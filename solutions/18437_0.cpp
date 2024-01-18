#include <bits/stdc++.h>

using namespace std;

// const int MAXN = 100;
const int MAXN = 100005;

int n, m, S[MAXN], E[MAXN], lazy[4*MAXN], tree[4*MAXN];
vector<int> adj[MAXN];

int cnt = 0;
void dfs(int node, int parent) {
    S[node] = ++cnt;
    for(auto next : adj[node]) 
        if(next != parent)
            dfs(next, node);
    E[node] = cnt - 1;
}

void propagate(int start, int end, int index) {
    if(lazy[index]) {
        if(lazy[index] < 0) tree[index] = 0;
        else tree[index] = (end - start + 1);

        if(start != end) {
            lazy[2*index] = lazy[index];
            lazy[2*index+1] = lazy[index];
        }
        lazy[index] = 0;
    }
}

void update(int start, int end, int index, int left, int right, int v) {
    propagate(start, end, index);
    if(end < left || right < start) return;

    if(left <= start && end <= right) {
        if(v < 0) tree[index] = 0;
        else tree[index] = (end - start + 1);

        if(start != end) {
            lazy[2*index] = v;
            lazy[2*index+1] = v;
        }
        return;
    }

    int mid = (start + end) / 2;
    update(start, mid, 2*index, left, right, v);
    update(mid+1, end, 2*index+1, left, right, v);
    tree[index] = tree[2*index] + tree[2*index+1];
}

int query(int start, int end, int index, int left, int right) {
    propagate(start, end, index);
    if(end < left || right < start) return 0;

    if(left <= start && end <= right) return tree[index];

    int mid = (start + end) / 2;
    return query(start, mid, 2*index, left, right) + query(mid+1, end, 2*index+1, left, right);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for(int i = 1; i <= n; i++) {
        int p; cin >> p;
        adj[p].push_back(i);
    }
    dfs(1, 0);
    update(0, n, 1, 0, n-1, 1);

    cin >> m;
    while(m--) {
        int type, i; cin >> type >> i;
        if(type == 1) {
            update(0, n, 1, S[i], E[i], 1);
        } else if(type == 2) {
            update(0, n, 1, S[i], E[i], -1);
        } else {
            int result = query(0, n, 1, S[i], E[i]);
            cout << result << "\n";
        }
    }
}