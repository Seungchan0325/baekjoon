#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF = 1e18;
const int MAXN = 250005;

bool vst[2*MAXN];
int N, S[MAXN], T[MAXN];
vector<int> graph[2*MAXN];
vector<int> v;

ll dfs(int u, int p)
{
    ll ret = v[u];
    vst[u] = true;
    for(auto v : graph[u]) {
        if(v == p) continue;
        if(vst[v]) return INF;
        ret = max(ret, dfs(v, u));
    }
    return ret;
}

int main()
{
    cin >> N;

    ll ans = 0;
    for(int i = 1; i <= N; i++) {
        cin >> S[i] >> T[i];
        v.push_back(S[i]);
        v.push_back(T[i]);
        ans += S[i];
        ans += T[i];
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    for(int i = 1; i <= N; i++) {
        int a = lower_bound(v.begin(), v.end(), S[i]) - v.begin();
        int b = lower_bound(v.begin(), v.end(), T[i]) - v.begin();
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for(int i = 0; i < v.size(); i++) {
        ans -= v[i];
        if(!vst[i]) {
            ll res = dfs(i, -1);
            if(res < INF) ans += res;
        }
    }
    cout << ans;
}