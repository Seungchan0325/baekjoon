#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10000 + 5;

int n, times[MAXN], in_deg[MAXN], dp[MAXN];
vector<int> adj[MAXN], radj[MAXN];

int main() {
    cin>>n;
    for(int i=1; i<=n; i++) {
        cin>>times[i];
        int prev; cin>>prev;
        in_deg[i] = prev;
        while(prev--) {
            int tmp; cin>>tmp;
            adj[tmp].push_back(i);
            radj[i].push_back(tmp);
        }
    }

    int ans = 0;
    queue<int> q;
    for(int i=1; i<=n; i++) {
        if(!in_deg[i]) {
            q.push(i);
            dp[i] = times[i];
            ans = max(ans, dp[i]);
        }
    }

    while(!q.empty()) {
        int cur = q.front(); q.pop();
        for(int next : adj[cur]) {
            if(--in_deg[next] == 0) {
                for(int prev : radj[next]) {
                    dp[next] = max(dp[prev], dp[next]);
                }
                dp[next] += times[next];
                ans = max(ans, dp[next]);
                q.push(next);
            }
        }
    }

    cout<<ans;
}