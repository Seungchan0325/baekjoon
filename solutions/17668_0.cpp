#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x, y, z;
    int q, i;
    auto operator <=> (const Point& rhs) const {
        return tuple(x,y,z) <=> tuple(rhs.x, rhs.y, rhs.z);
    }
};

struct Fenwick {
    int N;
    vector<int> tree;
    Fenwick(int N) : N(N), tree(N+1) {}

    void upd(int x, int v)
    {
        while(x <= N) {
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

int ans[101010];
vector<Point> pt;

void DnC(int l, int r)
{
    if(l == r) return;

    int m = (l + r) / 2;
    DnC(l, m);
    DnC(m+1, r);
    vector<Point> v;
    vector<int> xs = {-1};
    for(int i = l; i <= m; i++) {
        if(pt[i].q == 0) {
            v.push_back(pt[i]);
            xs.push_back(pt[i].z);
        }
    }
    for(int i = m+1; i <= r; i++) {
        if(pt[i].q == 1) {
            v.push_back(pt[i]);
        }
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    sort(v.begin(), v.end(), [](Point a, Point b){
        if(a.y != b.y) return a.y > b.y;
        if(a.z != b.z) return a.z > b.z;
        return a.q < b.q;
    });

    Fenwick f(xs.size());

    for(auto i : v) {
        int j = lower_bound(xs.begin(), xs.end(), i.z) - xs.begin();
        if(i.q) {
            ans[i.i] += f.qry(xs.size()) - f.qry(j-1);
        } else {
            f.upd(j, 1);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        pt.emplace_back(x, y, x+y, 0, 0);
    }
    for(int i = 0; i < q; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        pt.emplace_back(x, y, z, 1, i);
    }

    sort(pt.begin(), pt.end(), [](Point a, Point b){
        if(a.x != b.x) return a.x > b.x;
        if(a.y != b.y) return a.y > b.y;
        if(a.z != b.z) return a.z > b.z;
        return a.q < b.q;
    });

    DnC(0, ssize(pt)-1);
    for(int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }
}