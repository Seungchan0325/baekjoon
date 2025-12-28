#include <bits/stdc++.h>

using namespace std;

const int MAXN = 250505;
const int B = 500;

int N, K, Q, A[MAXN], tree[2*MAXN], f[MAXN], t[MAXN], l[MAXN], r[MAXN], x[MAXN];

void add(int x, int v)
{
    while(x < MAXN) {
        f[x] += v;
        x += x & -x;
    }
}

int qry(int x)
{
    int res = 0;
    while(x > 0) {
        res += f[x];
        x -= x & -x;
    }
    return res;
}

void update(int x, int v)
{
    tree[x+=MAXN] = v;
    while(x>>=1) tree[x] = tree[x<<1]|tree[x<<1|1];
}

int query(int l, int r)
{
    int res = 0;
    for(l+=MAXN, r+=MAXN; l<=r; l>>=1, r>>=1) {
        if(l&1) res |= tree[l++];
        if(~r&1) res |= tree[r--];
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> K;
    for(int i = 1; i <= N; i++) cin >> A[i];

    vector<tuple<int, int, int>> upds;
    cin >> Q;
    for(int i = 1; i <= Q; i++) {
        cin >> t[i] >> l[i] >> r[i];
        if(t[i] == 1) {
            cin >> x[i];
            upds.emplace_back(l[i], i, x[i]);
            upds.emplace_back(r[i]+1, i, 0);
        }
    }
    sort(upds.begin(), upds.end());
    vector<tuple<int, int, int>> tm;
    int j = 0;
    for(int i = 1; i <= N; i++) {
        while(j < upds.size() && get<0>(upds[j]) <= i) {
            auto [_, idx, v] = upds[j];
            update(idx, v);
            j++;
        }

        int lo = 0;
        int hi = Q+1;
        while(lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            if((A[i] | query(1, mid)) >= K) hi = mid;
            else lo = mid;
        }
        int s = hi;

        lo = 0;
        hi = Q+1;
        while(lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            if((A[i] | query(1, mid)) > K) hi = mid;
            else lo = mid;
        }
        int e = lo;

        if(s <= e) {
            tm.emplace_back(s, i, 1);
            tm.emplace_back(e+1, i, -1);
        }
    }
    sort(tm.begin(), tm.end());
    j = 0;
    for(int i = 1; i <= Q; i++) {
        while(j < tm.size() && get<0>(tm[j]) <= i) {
            auto [_, idx, dv] = tm[j];
            add(idx, dv);
            j++;
        }
        if(t[i] == 2) {
            int ans = qry(r[i]) - qry(l[i]-1);
            cout << ans << "\n";
        }
    }
}