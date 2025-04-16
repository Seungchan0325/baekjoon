#include <bits/stdc++.h>

using namespace std;

struct DSU {
    int N;
    vector<int> root;
    DSU(int _N) : N(_N) {
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

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n+2);
    vector<pair<int, int>> v;
    v.reserve(n);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        v.emplace_back(a[i], i);
    }

    sort(v.begin(), v.end());

    long long ans = 0;
    DSU left(n+2), right(n+2);
    for(int j = 0; j + 1 < n; j++) {
        int i = v[j].second;
        auto p = left.find(i-1);
        auto q = right.find(i+1);
        if(p == 0 || (q <= n && a[p] > a[q])) {
            ans += a[q];
        } else {
            ans += a[p];
        }
        left.merge(i-1, i);
        right.merge(i+1, i);
    }
    cout << ans;
}