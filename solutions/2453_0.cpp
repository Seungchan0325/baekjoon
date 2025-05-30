#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10101;

bool vst[MAXN];
int N, M, c[MAXN];
vector<pair<int, int>> g[MAXN];

void dfs(int u, int& s)
{
    s += c[u];
    vst[u] = true;
    for(auto [v, w] : g[u]) {
        if(vst[v]) continue;
        c[v] = c[u] * w;
        dfs(v, s);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    for(int T = 0; T < 5; T++) {
        cin >> N >> M;
        for(int i = 1; i <= N; i++) {
            g[i].clear();
            c[i] = 0;
            vst[i] = 0;
        }
        for(int i = 0; i < M; i++) {
            int s, u, v;
            cin >> s >> u >> v;
            g[u].emplace_back(v, s);
            g[v].emplace_back(u, s);
        }
        bool failed = false;
        vector<int> v;
        for(int i = 1; i <= N; i++) {
            if(vst[i] == false) {
                c[i] = 1;
                int sum = 0;
                dfs(i, sum);
                v.push_back(abs(sum));
            }
            for(auto [j, s] : g[i]) {
                if(c[i] * s != c[j]) {
                    failed = true;
                }
            }
        }
        if(failed) {
            cout << "-1\n";
            continue;
        }

        bitset<2*MAXN> dp1, dp2;
        dp1.set(N);
        for(auto i : v) {
            dp2 = (dp1<<i)|(dp1>>i);
            swap(dp1, dp2);
        }
        int ans = 1e9;
        for(int i = 0; i < 2*N; i++) {
            if(dp1.test(i)) {
                ans = min(ans, abs(i - N));
            }
        }
        cout << ans << "\n";
    }
}