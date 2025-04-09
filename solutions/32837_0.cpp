#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> a, b, c;
map<tuple<int, int, int>, int> cache;

int dp(int i, int j, int k)
{
    if(i < 0 && j < 0 && k < 0) return 0;
    if(cache.count({i, j, k})) return cache[{i, j, k}];
    int& ret = cache[{i, j, k}];
    ret = 1e9;
    auto up = [&](int m) {
        int ni = lower_bound(a.begin(), a.end(), m) - a.begin() - 1;
        int nj = lower_bound(b.begin(), b.end(), m) - b.begin() - 1;
        return dp(ni, nj, k) + 1;
    };

    auto down = [&](int m) {
        int nj = lower_bound(b.begin(), b.end(), m) - b.begin() - 1;
        int nk = lower_bound(c.begin(), c.end(), m) - c.begin() - 1;
        return dp(i, nj, nk) + 1;
    };

    if(i >= 0 && (j < 0 || b[j] <= a[i]) && (k < 0 || c[k] <= a[i])) {
        ret = min(ret, up(a[i] - 10000));
    }
    if(j >= 0 && (i < 0 || a[i] <= b[j]) && (k < 0 || c[k] <= b[j])) {
        ret = min(ret, up(b[j] - 10000));
        ret = min(ret, down(b[j] - 10000));
    }
    if(k >= 0 && (i < 0 || a[i] <= c[k]) && (j < 0 || b[j] <= c[k])) {
        ret = min(ret, down(c[k] - 10000));
    }
    return ret;
}

int main()
{
    cin >> n;
    for(int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        if(y < 0) a.push_back(x);
        if(y == 0) b.push_back(x);
        if(y > 0) c.push_back(x);
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    sort(c.begin(), c.end());
    int ans = dp((int)a.size()-1, (int)b.size()-1, (int)c.size()-1);
    cout << ans;
}