#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXC = 600000;

ll N, tree[4*MAXC];

void update(int x, ll v, int s = 0, int e = MAXC, int idx = 1)
{
    if(e < x || x < s) return;
    if(s == e) {
        tree[idx] = min(tree[idx], v);
        return;
    }
    int m = (s + e) / 2;
    update(x, v, s, m, 2*idx);
    update(x, v, m+1, e, 2*idx+1);
    tree[idx] = min(tree[2*idx], tree[2*idx+1]);
}

ll query(int l, int r, int s = 0, int e = MAXC, int idx = 1)
{
    if(e < l || r < s) return 1e18;
    if(l <= s && e <= r) return tree[idx];
    int m = (s + e) / 2;
    return min(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

void dfs(int idx, ll a, ll b, ll c, vector<ll>& A, vector<pair<ll, ll>>& out)
{
    if(idx == A.size()) {
        out.emplace_back(c - b, b - a);
        return;
    }

    dfs(idx + 1, a + A[idx], b, c, A, out);
    dfs(idx + 1, a, b + A[idx], c, A, out);
    dfs(idx + 1, a, b, c + A[idx], A, out);
}

int main()
{
    cin >> N;
    vector<ll> A(N);
    for(int i = 0; i < N; i++) cin >> A[i];
    int m = N / 2;
    vector<ll> front(A.begin(), A.begin() + m), back(A.begin() + m, A.end());
    vector<pair<ll, ll>> front_out, back_out;
    dfs(0, 0, 0, 0, front, front_out);
    dfs(0, 0, 0, 0, back, back_out);
    sort(front_out.begin(), front_out.end());
    sort(back_out.begin(), back_out.end());

    vector<ll> v;
    v.reserve(back_out.size());
    for(auto [a, b] : back_out) v.push_back(b);
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    fill(tree, tree + 4*MAXC, 1e18);

    ll ans = 1e18;
    int j = back_out.size() - 1;
    for(int i = 0; i < front_out.size(); i++) {
        while(j >= 0 && front_out[i].first + back_out[j].first >= 0) {
            int idx = lower_bound(v.begin(), v.end(), back_out[j].second) - v.begin();
            update(idx, back_out[j].first + back_out[j].second);
            j--;
        }
        int idx = lower_bound(v.begin(), v.end(), -front_out[i].second) - v.begin();
        ans = min(ans, front_out[i].first + front_out[i].second + query(idx, MAXC));
    }
    cout << ans;
}