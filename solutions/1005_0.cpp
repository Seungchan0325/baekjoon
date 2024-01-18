#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin>>t;
    while(t--) {
        int n, k, w; cin>>n>>k;
        int times[1005], in_deg[1005];
        vector<int> graph[1005];

        for(int i=0; i<n; i++) cin>>times[i];
        for(int i=0; i<k; i++) {
            int a, b; cin>>a>>b; a--; b--;
            in_deg[b]++;
            graph[a].push_back(b);
        }
        cin>>w; w--;

        int dp[1005];
        queue<int> que;

        for(int i=0; i<n; i++) {
            if(in_deg[i] == 0)
                que.push(i);
            dp[i] = times[i];
        }
        
        while(!que.empty()) {
            int cur = que.front(); que.pop();

            for(int next : graph[cur]) {
                dp[next] = max(dp[cur] + times[next], dp[next]);
                if(--in_deg[next] == 0)
                    que.push(next);
            }
        }

        cout<<dp[w]<<"\n";
    }
}