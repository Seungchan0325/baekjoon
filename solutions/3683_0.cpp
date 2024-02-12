#include <bits/stdc++.h>

using namespace std;

const int MAXV = 505;

bool chk[MAXV];
int c, d, v, owner[MAXV];
string arr[MAXV][2];
vector<int> g[MAXV];

bool match(int u)
{
    for(auto v : g[u]) {
        if(chk[v]) continue;
        chk[v] = true;
        if(owner[v] == -1 || match(owner[v])) {
            owner[v] = u;
            return true;
        }
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int tc;
    cin >> tc;
    while(tc--) {
        cin >> c >> d >> v;
        for(int i = 0; i < v; i++) {
            cin >> arr[i][0] >> arr[i][1];
        }

        for(int i = 0; i < v; i++) g[i].clear();

        for(int i = 0; i < v; i++) {
            for(int j = 0; j < v; j++) {
                if(arr[i][0] == arr[j][1] || arr[i][1] == arr[i][0]) {
                    if(arr[i][0][0] == 'C')
                        g[i].push_back(j);
                    else
                        g[j].push_back(i);
                }
            }
        }

        memset(owner, -1, sizeof(owner));
        int ans = 0;
        for(int i = 0; i < v; i++) {
            memset(chk, 0, sizeof(chk));
            if(match(i)) ans++;
        }
        ans = v - ans;
        cout << ans << "\n";
    }
}