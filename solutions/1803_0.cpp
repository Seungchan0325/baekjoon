#include <bits/stdc++.h>

using namespace std;

const int MAXNM = 100005;

bool decided[MAXNM], visited[MAXNM];
int n, m, arr[MAXNM], in_deg[MAXNM], ans[MAXNM];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> arr[i];
        arr[i] += n;
        in_deg[arr[i]]++;
    }
    for(int i = 1; i <= m; i++) {
        cin >> arr[n + i];
        in_deg[arr[n + i]]++;
    }

    queue<int> q;
    for(int i = 1; i <= n + m; i++) {
        if(in_deg[i] == 0) {
            q.push(i);
            visited[i] = true;
        }
    }

    while(!q.empty()) {
        int cur = q.front(); q.pop();
        if(decided[cur]) {
            ans[cur] = 0;
        } else {
            ans[cur] = 1;
            decided[arr[cur]] = true;
        }
        if(--in_deg[arr[cur]] == 0) {
            q.push(arr[cur]);
            visited[arr[cur]] = true;
        }
    }

    while(true) {
        int first = -1;
        for(int i = 1; i <= n + m; i++) {
            if(!visited[i] && decided[i]) {
                first = i;
                break;
            }
        }

        if(first < 0) {
            for(int i = 1; i <= n + m; i++) {
                if(!visited[i]) {
                    first = i;
                    break;
                }
            }
            if(first < 0) break;
        }

        q.push(first);
        visited[first] = true;

        while(!q.empty()) {
            int cur = q.front(); q.pop();
            if(decided[cur]) {
                ans[cur] = 0;
            } else {
                ans[cur] = 1;
                decided[arr[cur]] = true;
            }
            if(--in_deg[arr[cur]] == 0) {
                q.push(arr[cur]);
                visited[arr[cur]] = true;
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        cout << ans[i];
    }
    cout << "\n";
    for(int i = 1; i <= m; i++) {
        cout << ans[n + i];
    }
}