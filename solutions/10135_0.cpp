#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 200005;

struct Vec2 {
    ll x, y, idx;
    
    Vec2 operator + (const Vec2& rhs) const
    {
        return {x + rhs.x, y + rhs.y};
    }
};

struct Lamp {
    int x, y, k, idx;
};

struct Fenwick {
    int N;
    vector<int> tree;
    Fenwick(int N) : N(N), tree(N) {}

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

int N, X[MAXN], Y[MAXN], K[MAXN], ans[MAXN];
Vec2 R1, R2;
Fenwick fenwick(MAXN);

ll ccw(Vec2 p1, Vec2 p2, Vec2 p3)
{
    ll ret = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
    if(ret < 0) return -1;
    if(ret > 0) return 1;
    return 0;
}

void DnC(int l, int r, vector<Lamp> lamps)
{
    if(l == r) {
        for(auto i : lamps) {
            ans[i.idx] = l;
        }
        return;
    }
    int m = (l + r) / 2;
    vector<Lamp> left, right;
    for(auto i : lamps) {
        if(l <= i.idx && i.idx <= m) {
            fenwick.upd(i.y, 1);
            left.push_back(i);
            continue;
        }

        if(fenwick.qry(i.y) >= i.k) {
            fenwick.upd(i.y, 1);
            left.push_back(i);
        } else {
            i.k -= fenwick.qry(i.y);
            right.push_back(i);
        }
    }
    for(auto i : left) fenwick.upd(i.y, -1);
    DnC(l, m, left);
    DnC(m+1, r, right);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N;
    cin >> R1.x >> R1.y >> R2.x >> R2.y;
    if(ccw({0, 0}, R2, R1) < 0) swap(R1, R2);
    vector<Vec2> v(N);
    for(int i = 0; i < N; i++) {
        cin >> v[i].x >> v[i].y;
        v[i].idx = i+1;
    }

    sort(v.begin(), v.end(), [&] (Vec2 p1, Vec2 p2) {
        ll c = ccw(p1, p1 + R1, p2);
        if(c) return c < 0;
        Vec2 P = {R1.y, -R1.x};
        return ccw(p1, p1 + P, p2) > 0;
    } );
    for(int i = 0; i < N; i++) {
        X[v[i].idx] = i+1;
    }
    
    sort(v.begin(), v.end(), [&] (Vec2 p1, Vec2 p2) {
        ll c = ccw(p1, p1 + R2, p2);
        if(c) return c > 0;
        Vec2 P = {R2.y, -R2.x};
        return ccw(p1, p1 + P, p2) > 0;
    } );
    for(int i = 0; i < N; i++) {
        Y[v[i].idx] = i+1;
    }

    vector<Lamp> lamps;
    for(int i = 1; i <= N; i++) {
        cin >> K[i];
        lamps.push_back({X[i], Y[i], K[i], i});
    }

    sort(lamps.begin(), lamps.end(), [](Lamp a, Lamp b) {
        return tie(a.x, a.y) < tie(b.x, b.y);
    });

    DnC(1, N, lamps);

    for(int i = 1; i <= N; i++) {
        cout << ans[i] << " ";
    }
}