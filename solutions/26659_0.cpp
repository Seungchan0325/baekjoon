#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 250505;
const ll INF = 1e18;

struct T {
    ll a[4];
    T() : a{-INF, -INF, -INF, -INF} {}
    ll& operator [] (int idx) { return a[idx]; }
};

int N;
T tree[4*MAXN];

T merge(T a, T b)
{
    T ret;
    for(int i = 0; i < 4; i++) ret[i] = max(a[i], b[i]);
    ret[0b00] = max({ret[0b00], a[0b01] + b[0b00], a[0b00] + b[0b10]});
    ret[0b01] = max({ret[0b01], a[0b01] + b[0b01], a[0b00] + b[0b11]});
    ret[0b10] = max({ret[0b10], a[0b11] + b[0b00], a[0b10] + b[0b10]});
    ret[0b11] = max({ret[0b11], a[0b11] + b[0b01], a[0b10] + b[0b11]});
    return ret;
}

void update(int x, T v, int s = 1, int e = N, int idx = 1)
{
    if(e < x || x < s) return;
    if(s == e) {
        tree[idx] = v;
        return;
    }
    int m = (s + e) / 2;
    update(x, v, s, m, 2*idx);
    update(x, v, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N;
    vector<tuple<int, int, int, char>> v(N);
    vector<int> xs, ys;
    for(auto& [xl, xr, y, t] : v) {
        cin >> xl >> xr >> y >> t;
        xs.push_back(xl);
        ys.push_back(y);
    }
    sort(v.begin(), v.end());
    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    int idx = 0;
    ll ans = 0;
    priority_queue<pair<int, int>> pq;
    for(auto x : xs) {
        while(pq.size() && -pq.top().first < x) {
            update(pq.top().second, T());
            pq.pop();
        }
        while(idx < N && get<0>(v[idx]) <= x) {
            auto [xl, xr, y, t] = v[idx++];
            int yi = lower_bound(ys.begin(), ys.end(), y) - ys.begin() + 1;
            T upd;
            if(t == 'S') upd[0b00] = xr - xl + 1;
            if(t == 'D') upd[0b11] = xr - xl + 1;
            update(yi, upd);
            pq.emplace(-xr, yi);
        }
        ans = max({ans, tree[1][0], tree[1][1], tree[1][2], tree[1][3]});
    }
    cout << ans;
}