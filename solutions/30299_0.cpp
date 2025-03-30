#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 505050;

struct Fenwick {
    int N;
    vector<int> tree;
    Fenwick(int N) : N(N), tree(N+1) {}

    void upd(int x, int v)
    {
        while(x <= N) {
            tree[x] += v;
            x += x & -x;
        }
    }

    int qry(int x)
    {
        int ret = 0;
        while(x > 0) {
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }

    int kth(int k)
    {
        int lo = 0;
        int hi = N;
        while(lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            if(qry(mid) < k) lo = mid;
            else hi = mid;
        }
        return hi;
    }
};

ll N, Q, D, A[MAXN], ans[MAXN], mn = 1e18, l[MAXN], r[MAXN], d[MAXN], p[MAXN], s[MAXN], w[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i], mn = min(mn, A[i]);
    for(int i = 1; i <= N; i++) A[i] -= mn;
    sort(A+1, A+N+1);

    int i, j;
    l[1] = r[1] = 0;
    d[1] = 1;
    i = j = 1;

    while(i < N) {
        ll q = (A[i+1] - r[i] - 1) / d[i] + 1;
        ll li, ri, di;
        li = l[i] + d[i] * q;
        ri = r[i] + d[i] * q;
        di = d[i];
        s[i+1] = q;
        j = i + 1;
        while(j <= N && A[j] <= ri) {
            w[j] = A[j] - li + 1;
            ri++;
            di++;
            j++;
        }
        for(int k = i + 1; k < j; k++) {
            l[k] = li;
            r[k] = ri;
            d[k] = di;
            p[k] = i;
        }
        i = j - 1;
    }

    for(int i = 1; i <= N; i++) {
        s[i] += s[i-1];
    }
    
    cin >> Q >> D;
    vector<pair<ll, int>> q(Q);
    for(int i = 0; i < Q; i++) {
        q[i].second = i;
        cin >> q[i].first;
        if(q[i].first < mn) ans[i] = q[i].first;
        q[i].first -= mn;
    }
    sort(q.begin(), q.end(), greater<>());

    Fenwick ft(N), rft(N);
    for(int i = 1; i <= N; i++) ft.upd(i, 1), rft.upd(i, 1);

    j = N;
    int k = N;
    for(auto [x, i] : q) {
        if(x < 0) continue;

        while(A[j] > x) {
            ft.upd(ft.kth(w[j--]), -1);
        }

        int idx = upper_bound(A+1, A+N+1, x) - A - 1;
        int kth = ft.kth((x - l[idx]) % d[idx] + 1);
        ll dd = 0;
        if(r[idx] < x) {
            dd = (x - r[idx] + d[idx] - 1) / d[idx];
        }
        int start = -1;
        int lo = idx;
        int hi = N+1;
        while(lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            if(s[mid] - s[idx] - 1 < D + dd) lo = mid;
            else hi = mid;
        }
        start = lo;

        while(start < k) {
            rft.upd(rft.kth(w[k--]), -1);
        }

        kth = rft.qry(kth) - 1;

        ll block = D - (s[start] - s[idx]) + dd;

        ans[i] = l[start] + block * d[start] + kth + mn;
    }
    for(int i = 0; i < Q; i++) cout << ans[i] << "\n";
}