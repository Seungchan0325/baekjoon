#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50505;
const int inf = 1e9;

int n, a[MAXN];

struct Node {
    int mn = 0, mx = 0;
};

Node merge(Node a, Node b)
{
    return {min(a.mn, b.mn), max(a.mx, b.mx)};
}

struct SegTree {
    int n;
    vector<Node> t;
    void init(int _n) {
        n = _n;
        t.clear();
        t.resize(2*n);
    }
    void update(int x, Node v) {
        x += n;
        t[x] = v;
        while(x>>=1) {
            t[x] = merge(t[x<<1], t[x<<1|1]);
        }
    }
    Node query(int l, int r) {
        Node ret = {inf, -inf};
        for(l+=n, r+=n; l <= r; l>>=1, r>>=1) {
            if(l&1) ret = merge(ret, t[l++]);
            if(~r&1) ret = merge(ret, t[r--]);
        }
        return ret;
    }
};

vector<int> compute()
{
    vector<int> front(n+2), belong(2*n+2);
    SegTree owner; owner.init(2*n+2);
    for(int i = 1; i <= n; i++) owner.update(a[i], {a[i], a[i]});
    for(int i = 1; i <= n; i++) {
        auto find_first = [&]() {
            int lo = 0;
            int hi = 2*n;
            while(lo + 1 < hi) {
                int mid = (lo + hi) / 2;
                if(owner.query(1, mid).mn == 0) hi = mid;
                else lo = mid;
            }
            return hi;
        };
        front[i] = front[i-1];
        int j = find_first();
        auto dfs = [&](auto self, int k) -> bool {
            if(j < k) {
                owner.update(j, {k, k});
                belong[k] = j;
                return true;
            }
            int nxt = owner.query(1, k).mx;
            if(nxt <= k) return false;
            int be = belong[nxt];
            if(self(self, nxt)) {
                belong[k] = be;
                owner.update(belong[k], {k, k});
                return true;
            }
            return false;
        };
        if(dfs(dfs, a[i])) {
            front[i]++;
        }
    }
    return front;
}

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];

    reverse(a+1, a+n+1);
    auto back = compute();
    reverse(back.begin(), back.end());
    reverse(a+1, a+n+1);
    for(int i = 1; i <= n; i++) a[i] = 2*n - a[i] + 1;
    auto front = compute();

    int ans = 0;
    for(int i = 0; i <= n; i++) {
        ans = max(ans, front[i] + back[i+1]);
    }
    cout << ans << "\n";
}