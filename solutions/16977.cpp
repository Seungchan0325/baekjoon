#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

struct T {
    int lmx, rmx, mx;
    bool lable, rable, able;
};

T merge(T a, T b)
{
    T ret = {};
    ret.lable = a.lable;
    ret.rable = b.rable;
    ret.able = a.able && b.able;

    ret.lmx = a.lmx;
    if(a.able) ret.lmx = max(ret.lmx, a.lmx + b.lmx);
    ret.rmx = b.rmx;
    if(b.able) ret.rmx = max(ret.rmx, b.rmx + a.rmx);
    ret.mx = max({a.mx, b.mx, ret.lmx, ret.rmx});
    if(a.rable && b.lable) {
        ret.mx = max(ret.mx, a.rmx + b.lmx);
    }

    return ret;
}

struct Qry {
    int l, r, w, idx;
};

int N, h[MAXN], Q, L[MAXN], R[MAXN];
Qry qrys[MAXN];
T tree[4*MAXN];

void init(int s = 1, int e = N, int idx = 1)
{
    if(s == e) {
        tree[idx].able = tree[idx].lable = tree[idx].rable = true;
        tree[idx].mx = tree[idx].lmx = tree[idx].rmx = 1;
        return;
    }

    int m = (s + e) / 2;
    init(s, m, 2*idx);
    init(m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

void upd(int x, T v, int s = 1, int e = N, int idx = 1)
{
    if(e < x || x < s) return;

    if(s == e) {
        tree[idx] = v;
        return;
    }

    int m = (s + e) / 2;
    upd(x, v, s, m, 2*idx);
    upd(x, v, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

T qry(int l, int r, int s = 1, int e = N, int idx = 1)
{
    if(l <= s && e <= r) return tree[idx];

    int m = (s + e) / 2;
    if(l <= m && m+1 <= r) return merge(qry(l, r, s, m, 2*idx), qry(l, r, m+1, e, 2*idx+1));
    if(l <= m) return qry(l, r, s, m, 2*idx);
    return qry(l, r, m+1, e, 2*idx+1);
}

int main()
{
    cin >> N;
    vector<int> hs;
    for(int i = 1; i <= N; i++) {
        cin >> h[i];
        hs.push_back(h[i]);
    }
    sort(hs.begin(), hs.end());
    hs.erase(unique(hs.begin(), hs.end()), hs.end());
    cin >> Q;
    for(int i = 1; i <= Q; i++) {
        Qry q;
        cin >> q.l >> q.r >> q.w;
        L[i] = 0;
        R[i] = hs.size();
        q.idx = i;
        qrys[i] = q;
    }

    vector<vector<int>> updates(hs.size());
    vector<vector<int>> q(hs.size());
    for(int i = 1; i <= N; i++) {
        int idx = lower_bound(hs.begin(), hs.end(), h[i]) - hs.begin();
        updates[idx].push_back(i);
    }
    while(true) {
        for(int i = 0; i < hs.size(); i++) q[i].clear();
        bool isdone = true;
        for(int i = 1; i <= Q; i++) {
            if(L[i] + 1 < R[i]) {
                isdone = false;
                int m = (L[i] + R[i]) / 2;
                q[m].push_back(i);
            }
        }

        if(isdone) break;

        init();
        for(int i = 0; i < hs.size(); i++) {
            for(auto j : q[i]) {
                auto [l, r, w, idx] = qrys[j];
                auto t = qry(l, r);
                if(t.mx >= w) L[j] = i;
                else R[j] = i;
            }
            for(auto j : updates[i]) {
                T v = {0, 0, 0, false, false, false};
                upd(j, v);
            }
        }
    }

    for(int i = 1; i <= Q; i++) {
        auto [l, r, w, idx] = qrys[i];
        cout << hs[L[i]] << "\n";
    }
}