#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

int tree[3*4*MAXN], D[MAXN];
array<int, 3> A[MAXN];
vector<pair<int, int>> P;
vector<int> vs;

void update(int x, int v, int s = 0, int e = vs.size()-1, int idx = 1)
{
    if(e < x || x < s) return;
    if(s == e) {
        tree[idx] = v;
        return;
    }

    int m = (s + e) / 2;
    update(x, v, s, m, 2*idx);
    update(x, v, m+1, e, 2*idx+1);
    tree[idx] = max(tree[2*idx], tree[2*idx+1]);
}

int query(int l, int r, int s = 0, int e = vs.size()-1, int idx = 1)
{
    if(r < s || e < l) return 0;
    if(l <= s && e <= r) return tree[idx];
    int m = (s + e) / 2;
    return max(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

void DnC(int l, int r)
{
    if(l == r) return;
    int m = (l + r) / 2;
    DnC(l, m);
    vector<tuple<int, int, int, int>> p;
    p.reserve(r - l + 1);
    for(int i = l; i <= m; i++) {
        p.emplace_back(P[i].first, P[i].second, 0, i);
    }
    for(int i = m+1; i <= r; i++) {
        p.emplace_back(P[i].first, P[i].second, 1, i);
    }

    sort(p.begin(), p.end());
    for(auto [x, y, op, idx] : p) {
        if(op)
            D[idx] = max(D[idx], query(0, y) + 1);
        else
            update(y, D[idx]);
    }
    for(auto [x, y, op, idx] : p) {
        update(y, 0);
    }
    DnC(m+1, r);
}

int main()
{
    int M, N;
    cin >> M >> N;
    for(int i = 0; i < M; i++) {
        for(int j = 0; j < N; j++) {
            cin >> A[j][i];
            vs.push_back(A[j][i]);
        }
    }
    sort(vs.begin(), vs.end());
    vs.erase(unique(vs.begin(), vs.end()), vs.end());

    sort(A, A + N);

    if(M == 2) {
        for(int i = 0; i < N; i++) {
            int x = lower_bound(vs.begin(), vs.end(), A[i][0]) - vs.begin();
            int y = lower_bound(vs.begin(), vs.end(), A[i][1]) -  vs.begin();
            P.emplace_back(x, y);
        }
    } else {
        for(int i = 0; i < N; i++) {
            int x = lower_bound(vs.begin(), vs.end(), A[i][1]) - vs.begin();
            int y = lower_bound(vs.begin(), vs.end(), A[i][2]) -  vs.begin();
            P.emplace_back(x, y);
        }
    }

    for(int i = 0; i < N; i++) {
        D[i] = 1;
    }

    DnC(0, N-1);

    int ans = 0;
    for(int i = 0; i < N; i++) {
        ans = max(ans, D[i]);
    }
    cout << ans;
}