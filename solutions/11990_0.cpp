#include <bits/stdc++.h>

using namespace std;

struct Fenwick
{
    int n;
    vector<int> tree;
    void init(int _n)
    {
        n = _n;
        tree.resize(n+1);
    }
    void add(int x, int v)
    {
        while(x <= n) {
            tree[x] += v;
            x += x & -x;
        }
    }
    int qry(int x)
    {
        int ret = 0;
        while(x > 0) {
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }
};

const int MAXN = 101010;
const int MAXX = 1010101;

int N;
vector<int> ys[MAXX];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    Fenwick lef, rig;
    lef.init(MAXX);
    rig.init(MAXX);
    vector<int> v;
    for(int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        v.push_back(y);
        ys[x].push_back(y);
        rig.add(y, 1);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    int ans = 1e9;
    for(int i = 0; i < MAXX; i++) {
        if(ys[i].empty()) continue;
        auto compute = [&](int y) {
            return max({lef.qry(y), lef.qry(MAXX)-lef.qry(y), rig.qry(y), rig.qry(MAXX)-rig.qry(y)});
        };
        int lo = 0;
        int hi = ssize(v)-1;
        while(lo + 2 < hi) {
            int p = (2*lo+hi)/3;
            int q = (lo+2*hi)/3;
            if(compute(v[p]) < compute(v[q])) hi = q;
            else lo = p;
        }
        for(int j = lo; j <= hi; j++) ans = min(ans, compute(v[j]));
        for(auto y : ys[i]) rig.add(y, -1), lef.add(y, 1);
    }
    cout << ans << "\n";
}