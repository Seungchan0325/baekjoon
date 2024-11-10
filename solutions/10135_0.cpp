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
    }
};

int N, X[MAXN], Y[MAXN];
Vec2 R1, R2;

ll ccw(Vec2 p1, Vec2 p2, Vec2 p3)
{
    ll ret = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
    if(ret < 0) return -1;
    if(ret > 0) return 1;
    return 0;
}

int main()
{
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
}