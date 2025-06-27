#include <bits/stdc++.h>

using namespace std;

const int MAXQ = 202020;

struct T {
    int cnt;
    int ans;
    int width;
};

int q, w, x[MAXQ], y[MAXQ];
T tree[10*MAXQ];

void init(int s, int e, int idx, vector<int>& width)
{
    tree[idx].ans = tree[idx].cnt = 0;
    if(s == e) {
        tree[idx].width = width[s];
        return;
    }
    int m = (s + e) / 2;
    init(s, m, 2*idx, width);
    init(m+1, e, 2*idx+1, width);
    tree[idx].width = tree[2*idx].width + tree[2*idx+1].width;
}

void update(int l, int r, int dv, int s, int e, int idx)
{
    if(e < l || r < s) return;

    if(l <= s && e <= r) {
        tree[idx].cnt += dv;
        if(tree[idx].cnt) tree[idx].ans = tree[idx].width;
        else tree[idx].ans = tree[2*idx].ans + tree[2*idx+1].ans;
        return;
    }

    int m = (s + e) / 2;
    update(l, r, dv, s, m, 2*idx);
    update(l, r, dv, m+1, e, 2*idx+1);

    if(tree[idx].cnt) tree[idx].ans = tree[idx].width;
    else tree[idx].ans = tree[2*idx].ans + tree[2*idx+1].ans;
}

vector<int> solve()
{
    vector<int> vs;
    for(int i = 0; i < q; i++) {
        vs.push_back(x[i] - y[i]);
        vs.push_back(x[i] + y[i]);
    }
    sort(vs.begin(), vs.end());
    vs.erase(unique(vs.begin(), vs.end()), vs.end());

    vector<int> width;
    for(int i = 1; i < vs.size(); i++) {
        width.push_back(vs[i] - vs[i-1]);
    }

    multiset<int, greater<>> pq = {0};
    set<pair<int, int>> s;
    vector<int> ans(q);
    init(0, ssize(width)-1, 1, width);
    for(int i = 0; i < q; i++) {
        int dv = 1;
        if(s.contains(pair(x[i], y[i]))) {
            dv = -1;
            s.erase(pair(x[i], y[i]));
            pq.erase(pq.find(y[i] - x[i]));
        }
        else {
            dv = 1;
            s.insert(pair(x[i], y[i]));
            pq.insert(y[i] - x[i]);
        }

        int l = x[i] - y[i];
        int r = x[i] + y[i];
        l = lower_bound(vs.begin(), vs.end(), l) - vs.begin();
        r = lower_bound(vs.begin(), vs.end(), r) - vs.begin() - 1;
        update(l, r, dv, 0, ssize(width)-1, 1);
        ans[i] = tree[1].ans - 2 * (*pq.begin());
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> q >> w;
    for(int i = 0; i < q; i++) cin >> x[i] >> y[i];

    vector<int> ansl = solve();
    for(int i = 0; i < q; i++) x[i] = w - x[i];
    vector<int> ansr = solve();
    cout << fixed << setprecision(6);
    for(int i = 0; i < q; i++) {
        cout << (ansl[i] + ansr[i]) * sqrt(2) / 2.0 << "\n";
    }
}