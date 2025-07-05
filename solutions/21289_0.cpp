#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 303030;

ll N, K, x[MAXN], y[MAXN];
vector<ll> xs, rw[MAXN];
map<pair<ll, ll>, int> idx;

struct DSU {
    vector<int> par;
    DSU(int n) : par(n) { iota(par.begin(), par.end(), 0); }
    int find(int x)
    {
        if(par[x] == x) return x;
        return par[x] = find(par[x]);
    }
    void merge(int x, int y) 
    {
        x = find(x);
        y = find(y);
        par[y] = x;
    }
};

bool chk(ll k)
{
    DSU dsu(N+1);
    for(int i = 1; i < xs.size(); i++) {
        if(xs[i]-xs[i-1] != 1) continue;
        for(auto _y : rw[i]) {
            int j = upper_bound(rw[i-1].begin(), rw[i-1].end(), _y) - rw[i-1].begin() - 1;
            if(j+1 < rw[i-1].size() && rw[i-1][j+1] == _y+1) continue;
            if(j >= 0 && _y - rw[i-1][j] <= k) {
                dsu.merge(idx[pair(xs[i], _y)], idx[pair(xs[i-1], rw[i-1][j])]);
            }
        }
        
        for(auto _y : rw[i-1]) {
            int j = upper_bound(rw[i].begin(), rw[i].end(), _y) - rw[i].begin() - 1;
            if(j+1 < rw[i].size() && rw[i][j+1] == _y+1) continue;
            if(j >= 0 && _y - rw[i][j] <= k) {
                dsu.merge(idx[pair(xs[i-1], _y)], idx[pair(xs[i], rw[i][j])]);
            }
        }
    }

    return dsu.find(1) == dsu.find(N);
}

int main()
{
    cin >> N >> K;
    for(int i = 1; i <= N; i++) {
        cin >> x[i] >> y[i];
        idx[pair(x[i], y[i])] = i;
    }

    for(int i = 1; i <= N; i++) xs.push_back(x[i]);
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    for(int i = 1; i <= N; i++) {
        int j = lower_bound(xs.begin(), xs.end(), x[i]) - xs.begin();
        rw[j].push_back(y[i]);
    }
    for(int i = 0; i < xs.size(); i++) sort(rw[i].begin(), rw[i].end());

    ll lo = -1;
    ll hi = K;
    while(lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        if(chk(mid)) hi = mid;
        else lo = mid;
    }

    if(hi >= K) cout << "NATT\n";
    else cout << hi << "\n";
}