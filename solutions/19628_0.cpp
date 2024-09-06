#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 100005;

int N, M;
set<int> s[MAXN];

int main()
{
    cin >> N >> M;
    for(int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        if(u > v) swap(u, v);
        s[u].insert(v);
    }

    ll ans = 0;

    for(int i = 1; i <= N; i++) {
        if(s[i].size() && i == *s[i].begin()) s[i].erase(s[i].begin());
        ans += s[i].size();
        if(s[i].size()) {
            int nxt = *s[i].begin();
            if(s[i].size() > s[nxt].size()) {
                swap(s[i], s[nxt]);
            }
            s[nxt].insert(s[i].begin(), s[i].end());
        }
    }

    cout << ans;
}