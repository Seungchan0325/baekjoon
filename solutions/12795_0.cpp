#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF = 1e18;

struct Line {
    ll a, b;
    ll get(ll x) {
        return a * x + b;
    }
};

struct Node {
    int l, r;
    ll s, e;
    Line line;
};

int Q;

struct Li_Chao {
    vector<Node> tree;

    void init(ll s, ll e) {
        tree.push_back({-1, -1, s, e, {0, -INF}});
    }

    void update(int node, Line v) {
        ll s = tree[node].s;
        ll e = tree[node].e;
        ll m = (s + e) / 2;
        Line low = tree[node].line;
        Line high = v;
        if(low.get(s) > high.get(s)) swap(low, high);

        if(low.get(e) <= high.get(e)) {
            tree[node].line = high;
            return;
        }

        if(low.get(m) < high.get(m)) {
            tree[node].line = high;
            if(tree[node].r == -1) {
                tree[node].r = tree.size();
                tree.push_back({-1, -1, m+1, e, {0, -INF}});
            }
            update(tree[node].r, low);
        } else {
            tree[node].line = low;
            if(tree[node].l == -1) {
                tree[node].l = tree.size();
                tree.push_back({-1, -1, s, m, {0, -INF}});
            }
            update(tree[node].l, high);
        }
    }

    ll query(int node, ll x) {
        if(node == -1) return -INF;
        ll s = tree[node].s;
        ll e = tree[node].e;
        ll m = (s + e) / 2;
        if(x <= m) return max(tree[node].line.get(x), query(tree[node].l, x));
        else return max(tree[node].line.get(x), query(tree[node].r, x));
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> Q;
    Li_Chao tree;
    tree.init(-2e12, 2e12);
    while(Q--) {
        int op;
        cin >> op;
        if(op == 1) {
            ll a, b;
            cin >> a >> b;
            tree.update(0, {a, b});
        } else {
            ll x;
            cin >> x;
            ll result = tree.query(0, x);
            cout << result << "\n";
        }
    }
}