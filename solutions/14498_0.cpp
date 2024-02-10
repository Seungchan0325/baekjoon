#include <bits/stdc++.h>

using namespace std;

const int MAXK = 600;

bool chk[MAXK];
int n, m, k, arr[MAXK][3], owner[MAXK];
vector<int> g[MAXK];

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

    cin >> n >> m >> k;
    for(int i = 0; i < k; i++) {
        cin >> arr[i][0] >> arr[i][1] >> arr[i][2];
    }

    for(int i = 0; i < k; i++) {
        for(int j = 0; j < k; j++) {
            if((arr[i][0] == arr[j][0] || arr[i][1] == arr[j][1]) && (arr[i][2] != arr[j][2])) {
                if(arr[i][2]) g[i].push_back(j);
                else g[j].push_back(i);
            }
        }
    }

    memset(owner, -1, sizeof(owner));
    int ans = 0;
    for(int i = 0; i < k; i++) {
        memset(chk, 0, sizeof(chk));
        if(match(i)) ans++;
    }
    cout << ans;
}