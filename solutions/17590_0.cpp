#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

using ll = long long;

const int MAXN = 404040;

struct AB {
    ll a, b, i;
    bool operator < (const AB& t) const {
        if((b-a>=0) != (t.b-t.a>=0)) return b-a<0;
        if(b-a>=0) return a > t.a;
        else return b < t.b;
    }

    bool operator > (const AB& t) const {
        if((b-a>=0) != (t.b-t.a>=0)) return b-a>=0;
        if(b-a>=0) return a < t.a;
        else return b > t.b;
    }
};

ll T, n, x[MAXN], y[MAXN], a[MAXN], b[MAXN], par[MAXN], uf[MAXN];

int find(int x)
{
    if(uf[x] == x) return x;
    return uf[x] = find(uf[x]);
}

void mrg(int x, int y)
{
    x = find(x);
    y = find(y);
    if(x == y) return;
    uf[y] = x;
    a[x] = -min(-a[x], -a[x]+b[x]-a[y]);
    b[x] = max(b[y], b[x]-a[y]+b[y]);
}

template<class comp>
int solve()
{
    for(int i = 1; i <= 2*n; i++) {
        uf[i] = i;
        a[i] = y[i];
        b[i] = x[i];
    }

    priority_queue<AB, vector<AB>, comp> pq;
    for(int i = 1; i <= 2*n; i++) {
        if(i == 1 || i == n+1) continue;
        pq.push({a[i], b[i], i});
    }
    while(pq.size()) {
        auto ab = pq.top(); pq.pop();
        if(ab.a != a[ab.i] || ab.b != b[ab.i]) continue;
        mrg(par[ab.i], ab.i);
        int p = find(ab.i);
        if(p != 1 && p != n+1) pq.push({a[p], b[p], p});
    }

    return a[1];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    T = 1;
    while(T--) {
        cin >> n;
        for(int i = 2; i <= n; i++) {
            par[i] = i+n;
            y[i] = 1;
            cin >> par[i+n]; par[i+n]++;
            cin >> x[i];
            if(x[i] == -1) x[i] = 1e14;
            cin >> y[i+n]; y[i+n]--;
        }

        // cout << solve<greater<AB>>() << " ";

        cout << solve<greater<AB>>() << " " << solve<less<AB>>() << "\n";
    }
}
