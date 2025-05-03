#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50;

int N, C[MAXN], P[MAXN], K, M;

void dfs(int s, int e, int c, int p, vector<pair<int, int>>& v)
{
    if(s == e) {
        v.emplace_back(p, c);
        return;
    }
    dfs(s+1, e, c, p, v);
    dfs(s+1, e, c+C[s], p+P[s], v);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 0; i < N; i++) cin >> C[i];
    for(int i = 0; i < N; i++) cin >> P[i];
    cin >> K;
    int m; cin >> m;
    for(int i = 0; i < m; i++) {
        int a; cin >> a;
        M += C[a];
    }

    vector<pair<int, int>> left, right;
    dfs(0, N/2, 0, 0, left);
    dfs(N/2, N, 0, 0, right);
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    for(int i = ssize(left)-2; i >= 0; i--)
        left[i].second = min(left[i].second, left[i+1].second);
    for(int i = ssize(right)-2; i >= 0; i--)
        right[i].second = min(right[i].second, right[i+1].second);
    int ans = 1e9 + 7;
    for(int i = 0; i < ssize(left); i++) {
        int j = lower_bound(right.begin(), right.end(), pair(K-left[i].first, 0)) - right.begin();
        if(j != right.size())
            ans = min(ans, left[i].second + right[j].second - M);
    }
    ans = max(ans, 0);
    if(ans > 1e9) cout << "-1";
    else cout << ans;
}