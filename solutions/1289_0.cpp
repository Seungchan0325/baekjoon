#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 100001;
const int MOD = 1'000'000'007;

int n;
ll ans;
vector<pair<int, int>> adjlist[MAXN];

ll dfs(int node, int parent) {
    ll sum = 1;

    for(auto [child, w] : adjlist[node]) {
        if(parent == child) continue;

        ll nsum = (dfs(child, node) * w) % MOD;

        ans += (nsum * sum) % MOD;
        ans %= MOD;

        sum += nsum;
        sum %= MOD;
    }

    return sum;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n;
    for(int i=0; i<n-1; i++) {
        int a, b, w; cin>>a>>b>>w;
        adjlist[a].push_back({b, w});
        adjlist[b].push_back({a, w});
    }

    dfs(1, -1);

    cout<<ans;
}