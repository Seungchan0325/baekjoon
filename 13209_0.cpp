#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 100005;

int n, k, used;
ll sum, people[MAXN];
vector<int> children[MAXN];

ll dfs(int node, int parent, ll limit) {
    vector<ll> v;
    for(int child : children[node]) {
        if(child == parent) continue;
        v.push_back(dfs(child, node, limit));
    }

    ll ret = people[node];
    sort(v.begin(), v.end());
    for(ll i : v) {
        if(ret + i > limit) used++;
        else ret += i;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int t; cin>>t;
    while(t--) {
        cin>>n>>k;
        for(int i=1; i<=n; i++) { cin>>people[i]; sum += people[i]; }
        for(int i=1; i<n; i++) {
            int u, v; cin>>u>>v;
            children[u].push_back(v);
            children[v].push_back(u);
        }

        ll l = *max_element(people, people + n + 1), r = sum;
        while(l < r) {
            ll limit = (l + r) / 2;
            used = 0;
            dfs(1, -1, limit);

            if(used <= k) {
                r = limit;
            } else {
                l = limit + 1;
            }
        }

        cout<<l<<"\n";

        sum = 0;
        for(int i=0; i<=n; i++) children[i].clear();
    }
}