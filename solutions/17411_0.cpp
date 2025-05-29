#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010101;
const int MOD = 1e9 + 7;
const int INF = MOD;

struct Fenwick {
    int n;
    vector<int> tree, xs;
    Fenwick(vector<int> _xs) : xs(_xs)
    {
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        n = xs.size();
        tree.resize(n+1);
    }
    void update(int x, int v)
    {
        x = lower_bound(xs.begin(), xs.end(), x) - xs.begin() + 1;
        while(x <= n) {
            tree[x] += v;
            tree[x] %= MOD;
            x += x & -x;
        }
    }
    int query(int x)
    {
        x = upper_bound(xs.begin(), xs.end(), x) - xs.begin();
        int ret = 0;
        while(x > 0) {
            ret += tree[x];
            ret %= MOD;
            x -= x & -x;
        }
        return ret;
    }
};

int N, A[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i];

    vector<int> v;
    vector<vector<int>> vv;
    v.push_back(-INF);
    vv.push_back({-INF});
    for(int i = 1; i <= N; i++) {
        if(v.empty() || v.back() < A[i]) {
            v.push_back(A[i]);
            vv.push_back({A[i]});
        } else {
            int j = lower_bound(v.begin(), v.end(), A[i]) - v.begin();
            v[j] = A[i];
            vv[j].push_back(A[i]);
        }
    }

    vector<Fenwick> f;
    for(int i = 0; i < v.size(); i++) {
        f.push_back(Fenwick(vv[i]));
    }
    f[0].update(-INF, 1);

    v.clear();
    v.push_back(-INF);
    for(int i = 1; i <= N; i++) {
        if(v.empty() || v.back() < A[i]) {
            int q = f[ssize(v)-1].query(A[i] - 1);
            f[ssize(v)].update(A[i], q);
            v.push_back(A[i]);
        } else {
            int j = lower_bound(v.begin(), v.end(), A[i]) - v.begin();
            int q = f[j-1].query(A[i]-1);
            f[j].update(A[i], q);
            v[j] = A[i];
        }
    }
    cout << ssize(v) - 1 << " " << f[ssize(v)-1].query(INF);
}