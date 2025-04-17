#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50505;

using i5 = array<long long, 5>;

struct DSU {
    vector<int> root;
    DSU(int n) : root(n+1) {
        iota(root.begin(), root.end(), 0);
    }
    int find(int x)
    {
        if(root[x] == x) return x;
        return root[x] = find(root[x]);
    }
    void merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        root[y] = x;
    }
};

int N, M, Q;
map<i5, i5> computed;
vector<tuple<int, int, int>> edges;
 
i5 mst(i5 cost)
{
    sort(edges.begin(), edges.end(), [&](tuple<int, int, int> a, tuple<int, int, int> b){
        return cost[get<2>(a)] < cost[get<2>(b)];
    });
    i5 ret = {};
    DSU dsu(N);
    for(auto [u, v, w] : edges) {
        if(dsu.find(u) != dsu.find(v)) {
            dsu.merge(u, v);
            ret[w]++;
        }
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M >> Q;
    for(int i = 0; i < M; i++) {
        int u, v;
        char c;
        cin >> u >> v >> c;
        int w = c - 'A';
        edges.emplace_back(u, v, w);
    }

    i5 cost = {0, 1, 2, 3, 4};
    do {
        computed[cost] = mst(cost);
    } while(next_permutation(cost.begin(), cost.end()));

    while(Q--) {
        i5 cost;
        vector<pair<int, int>> v(5);
        for(int i = 0; i < 5; i++) {
            cin >> cost[i];
            v[i].first = cost[i];
            v[i].second = i;
        }
        sort(v.begin(), v.end());
        i5 c;
        for(int i = 0; i < 5; i++) {
            c[v[i].second] = i;
        }
        i5 table = computed[c];
        long long ans = 0;
        for(int i = 0; i < 5; i++) {
            ans += table[i] * cost[i];
        }
        cout << ans << "\n";
    }
}