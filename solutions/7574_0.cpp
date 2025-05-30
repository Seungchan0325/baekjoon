#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

bool vst[MAXN];
int N, r, d, S;
vector<int> g[MAXN];

void connect(vector<tuple<int, int, int>> flower)
{
    sort(flower.begin(), flower.end());
    set<pair<int, int>> s;
    int idx = 0;
    for(auto [x, y, i] : flower) {
        while(idx < N && x - get<0>(flower[idx]) > r + d) {
            s.erase(pair(get<1>(flower[idx]), get<2>(flower[idx])));
            idx++;
        }
        auto it = s.lower_bound(pair(y - r, -1));
        while(it != s.end() && it->first <= y + r) {
            int j = it->second;
            g[i].push_back(j);
            g[j].push_back(i);
            it++;
        }
        s.insert(pair(y, i));
    }
}

void dfs(int u)
{
    vst[u] = true;
    for(auto v : g[u]) {
        if(vst[v]) continue;
        dfs(v);
    }
}

int main()
{
    cin >> N >> r;
    vector<tuple<int, int, int>> flower(N);
    for(int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        flower[i] = tuple(x, y, i+1);
        if(x == 0 && y == 0) S = i+1;
    }
    cin >> d;
    connect(flower);
    for(auto& [x, y, i] : flower) swap(x, y);
    connect(flower);

    dfs(S);
    int ans = 0;
    for(auto [x, y, i] : flower) {
        if(vst[i]) ans = max(ans, x+y+r+r);
    }
    cout << ans;
}