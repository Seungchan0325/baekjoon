#include <bits/stdc++.h>

using namespace std;

struct DSU {
    int N;
    vector<int> root;
    DSU(int _N = 0) : N(_N) {
        root.resize(N+1);
        iota(root.begin(), root.end(), 0);
    }

    void init(int _n)
    {
        N = _n;
        root.resize(N+1);
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

const int MAXN = 303030;

int N, K, H[MAXN], chk[MAXN], ans;
DSU dsu;

int go(int i, int di)
{
    int h = H[i];
    while(1 <= i && i <= N) {
        i += di;
        if(H[i] > h) break;
        h = H[i];
    }
    return i;
}

void update(int l, int r)
{
    for(int i = dsu.find(l); i <= r; i = dsu.find(i)) {
        dsu.merge(i+1, i);
        chk[i] = 1;
        ans++;
    }
}

int main()
{
    cin >> N >> K;
    dsu.init(N+5);
    for(int i = 1; i <= N; i++) cin >> H[i];
    vector<int> t;
    for(int i = 1; i <= N; i++) {
        char c; cin >> c;
        if(c == 'T') t.push_back(i);
    }
    vector<pair<int, int>> rightdown, leftdown;
    for(int i = 1; i <= N;) {
        int j = go(i, 1);
        rightdown.emplace_back(i, j-1);
        i = j;
    }
    for(int i = N; i >= 1;) {
        int j = go(i, -1);
        leftdown.emplace_back(j+1, i);
        i = j;
    }

    bool jump = false;
    int l, r, i;
    l = go(K, -1)+1;
    r = K;
    i = lower_bound(t.begin(), t.end(), l) - t.begin();
    if(0 <= i && i < t.size() && t[i] <= r) update(t[i], r), jump = true;
    l = K;
    r = go(K, 1)-1;
    i = upper_bound(t.begin(), t.end(), r) - t.begin() - 1;
    if(0 <= i && i < t.size() && l <= t[i]) update(l, t[i]), jump = true;

    if(!jump) {
        int a = K;
        int b = K;
        while(a > 1 && H[a-1] == H[K]) a--;
        while(b < N && H[b+1] == H[K]) b++;
        l = go(a, -1);
        r = go(b, 1);
        cout << max(a-l, r-b) + b-a << "\n";
        return 0;
    }

    for(auto [l, r] : rightdown) {
        int i = upper_bound(t.begin(), t.end(), r) - t.begin() - 1;
        if(0 <= i && i < t.size()) update(l, t[i]);
    }
    for(auto [l, r] : leftdown) {
        int i = lower_bound(t.begin(), t.end(), l) - t.begin();
        if(0 <= i && i < t.size()) update(t[i], r);
    }

    for(int i = 1; i <= N; i++) {
        chk[i] = 1 - chk[i];
        chk[i] += chk[i-1];
    }

    int mx = 0;
    for(auto [l, r] : rightdown) {
        mx = max(mx, chk[r] - chk[l-1]);
    }
    for(auto [l, r] : leftdown) {
        mx = max(mx, chk[r] - chk[l-1]);
    }
    ans += mx;

    cout << ans;
}