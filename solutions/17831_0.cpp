#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

int n, v[MAXN], dp1[MAXN], dp2[MAXN];
vector<int> childs[MAXN];

void dfs(int node) {
    int sum = 0;
    for(auto child : childs[node]) {
        dfs(child);
        sum += dp1[child];
    }

    dp1[node] = sum;
    for(auto child : childs[node]) {
        dp1[node] = max(v[node] * v[child] + dp2[child] + sum - dp1[child], dp1[node]);
        dp2[node] += dp1[child];
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n;
    for(int i=2; i<=n; i++) {
        int p; cin>>p;
        childs[p].push_back(i);
    }
    for(int i=1; i<=n; i++) cin>>v[i];

    dfs(1);
    cout<<dp1[1];
}