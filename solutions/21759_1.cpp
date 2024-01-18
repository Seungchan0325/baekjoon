#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 200001;
const ll INF = 1e18;

int n;
ll skills[MAXN], dp1[MAXN], dp2[MAXN], dp3[MAXN], ans;
vector<int> childs[MAXN];

void dfs(int node) {
    dp1[node] = skills[node];
    dp2[node] = -INF;

    priority_queue<ll> pq;

    for(auto child : childs[node]) {
        dfs(child);

        if(dp1[child] > 0) {
            dp1[node] += dp1[child];
            dp2[node] = max(dp2[node], dp2[child]);
        }
        else {
            dp2[node] = max(dp2[node], dp3[child]);
        }
        pq.push(dp3[child]);
    }

    dp3[node] = dp1[node];

    ans = max(ans, dp1[node] + dp2[node]);

    if(!pq.empty()) {
        dp3[node] = max(dp3[node], pq.top());
        ll tmp = pq.top(); pq.pop();
        if(!pq.empty())
            ans = max(ans, tmp + pq.top());
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n;
    for(int i=1; i<=n; i++) {
        int parent;
        cin>>skills[i]>>parent;

        if(parent > 0) {
            childs[parent].push_back(i);
        }
    }

    dfs(1);
    cout<<ans;
}