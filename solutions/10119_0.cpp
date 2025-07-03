#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 250505;

int n, q, a, d[MAXN], tree[4*MAXN];

int merge(int i, int j)
{
    if(i == 0 || i == a) return j;
    if(j == 0 || j == a) return i;
    return (d[i] < d[j]) ? j : i;
}

void init(int s = 1, int e = n, int idx = 1)
{
    if(s == e) {
        tree[idx] = s;
        return;
    }
    int m = (s + e) / 2;
    init(s, m, 2*idx);
    init(m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

void update(int x, int s = 1, int e = n, int idx = 1)
{
    if(e < x || x < s) return;
    if(s == e) return;
    int m = (s + e) / 2;
    update(x, s, m, 2*idx);
    update(x, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

int query(int l, int r, int s = 1, int e = n, int idx = 1)
{
    if(e < l || r < s) return 0;
    if(l <= s && e <= r) return tree[idx];
    int m = (s + e) / 2;
    return merge(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> a;
    set<pair<int, int>, greater<>> pq;
    for(int i = 1; i <= n; i++) {
        cin >> d[i];
        pq.emplace(d[i], i);
    }
    init();
    cin >> q;
    while(q--) {
        char c;
        cin >> c;

        if(c == 'E') {
            int i, e; cin >> i >> e;
            auto it = pq.begin();
            vector<int> v; v.reserve(10);
            for(int j = 1; j < e; j++) {
                v.push_back(it->second);
                it++;
            }
            for(auto j : v) {
                pq.erase({d[j], j});
                pq.insert({++d[j], j});
                update(j);
            }
            it = pq.begin();
            for(int j = 1; j < e; j++) it++;
            pq.erase({d[i], i});
            d[i] = it->first+1;
            pq.insert({d[i], i});
            update(i);
        } else if(c == 'F') {
            int b; cin >> b;

            if(b <= a) {
                int i = query(b, a);
                int lo = a;
                int hi = n+1;
                while(lo + 1 < hi) {
                    int mid = (lo + hi) / 2;
                    if(d[query(a, mid)] <= d[i]) lo = mid;
                    else hi = mid;
                }
                int ans = lo - b;
                cout << ans << "\n";
            } else {
                int i = query(a, b);
                int lo = 0;
                int hi = a;
                while(lo + 1 < hi) {
                    int mid = (lo + hi) / 2;
                    if(d[query(mid, a)] <= d[i]) hi = mid;
                    else lo = mid;
                }
                int ans = b - hi;
                cout << ans << "\n";
            }
        }
    }
}