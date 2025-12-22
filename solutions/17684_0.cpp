#include <bits/stdc++.h>

using namespace std;

bool vst[22];
int n, k, w0;
vector<int> g[22];

int bfs(int u)
{
    for(int i = 1; i <= n; i++) vst[i] = false;
    vst[u] = true;
    int ret = 0;
    queue<int> q;
    q.push(u);
    int dep = 0;
    while(q.size()) {
        int sz = q.size();
        while(sz--) {
            int now = q.front(); q.pop();
            ret += dep;
            for(auto nxt : g[now]) {
                if(vst[nxt]) continue;
                vst[nxt] = true;
                q.push(nxt);
            }
        }
        dep++;
    }
    return ret;
}

int eval()
{
    int ret = 0;
    for(int i = 1; i <= n; i++) {
        ret += bfs(i);
    }
    return ret;
}

int main()
{
    cin >> n >> k >> w0;
    for(int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    tuple<int, int, int, int, int, int> ans = {1e9, -1, -1, -1, -1, -1};
    for(int center = 1; center <= n; center++) {
        for(int a = 1; a <= n; a++) {
            if(a == center) continue;
            for(int b = a+1; b <= n; b++) {
                if(b == center) continue;
                for(int c = b+1; c <= n; c++) {
                    if(c == center) continue;
                    for(int d = c+1; d <= n; d++) {
                        if(d == center) continue;
                        g[center].push_back(a);
                        g[center].push_back(b);
                        g[center].push_back(c);
                        g[center].push_back(d);
                        g[a].push_back(center);
                        g[b].push_back(center);
                        g[c].push_back(center);
                        g[d].push_back(center);
                        ans = min(ans, {eval(), center, a, b, c, d});
                        g[center].pop_back();
                        g[center].pop_back();
                        g[center].pop_back();
                        g[center].pop_back();
                        g[a].pop_back();
                        g[b].pop_back();
                        g[c].pop_back();
                        g[d].pop_back();
                    }
                }
            }
        }
    }

    auto [e, center, a, b, c, d] = ans;
    cout << center << " " << a << "\n";
    cout << center << " " << b << "\n";
    cout << center << " " << c << "\n";
    cout << center << " " << d << "\n";
}