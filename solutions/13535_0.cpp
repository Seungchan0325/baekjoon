#include <bits/stdc++.h>

using namespace std;

struct Seg
{
    int n;
    vector<int> tree;
    Seg(const vector<int>& v)
    {
        n = v.size();
        tree.resize(4*n);
        init(v, 0, n-1, 1);
    }
    void init(const vector<int>& v, int s, int e, int idx)
    {
        if(s == e) {
            tree[idx] = v[s];
            return;
        }
        int m = (s + e) / 2;
        init(v, s, m, 2*idx);
        init(v, m+1, e, 2*idx+1);
        tree[idx] = min(tree[2*idx], tree[2*idx+1]);
    }
    int Q(int l, int r, int x)
    {
        if(rmq(l, r, 0, n-1, 1) > x) return -1;
        r = min(r, first_lt(l, x, 0, n-1, 1)-1);
        return last_eq(l, r, x, 0, n-1, 1);
    }
    int rmq(int l, int r) {return rmq(l, r, 0, n-1, 1);};
    int rmq(int l, int r, int s, int e, int idx)
    {
        if(e < l || r < s) return 1e9;
        if(l <= s && e <= r) return tree[idx];
        int m = (s + e) / 2;
        return min(rmq(l, r, s, m, 2*idx), rmq(l, r, m+1, e, 2*idx+1));
    }
    int first_lt(int l, int x) {return first_lt(l, x, 0, n-1, 1);}
    int first_lt(int l, int x, int s, int e, int idx)
    {
        if(e < l) return n;
        if(l <= s && tree[idx] >= x) return n;
        if(s == e) return s;
        int m = (s + e) / 2;
        int lef = first_lt(l, x, s, m, 2*idx);
        if(lef < n) return lef;
        return first_lt(l, x, m+1, e, 2*idx+1);
    }
    int last_eq(int l, int r, int x) {return last_eq(l, r, x, 0, n-1, 1);}
    int last_eq(int l, int r, int x, int s, int e, int idx)
    {
        if(e < l || r < s) return -1;
        if(l <= s && e <= r && tree[idx] > x) return -1;
        if(s == e) return s;
        int m = (s + e) / 2;
        int rig = last_eq(l, r, x, m+1, e, 2*idx+1);
        if(rig >= 0) return rig;
        return last_eq(l, r, x, s, m, 2*idx);
    }
};

struct MergeSortTree {
    int n;
    vector<vector<int>> tree;
    MergeSortTree(const vector<int>& v)
    {
        n = v.size();
        tree.resize(4*n);
        init(v, 0, n-1, 1);
    }
    void init(const vector<int>& v, int s, int e, int idx) {
        if(s == e) {
            tree[idx].push_back(v[s]);
            return;
        }
        int m = (s + e) / 2;
        init(v, s, m, 2*idx);
        init(v, m+1, e, 2*idx+1);
        tree[idx].resize(tree[2*idx].size() + tree[2*idx+1].size());
        merge(tree[2*idx].begin(), tree[2*idx].end(),
              tree[2*idx+1].begin(), tree[2*idx+1].end(),
              tree[idx].begin());
    }
    int Q(int l, int r, int x, int y)
    {
        return query(l, r, x, y, 0, n-1, 1);
    }
    int query(int l, int r, int x, int y, int s, int e, int idx)
    {
        if(e < l || r < s) return 0;
        if(l <= s && e <= r) return upper_bound(tree[idx].begin(), tree[idx].end(), y) - lower_bound(tree[idx].begin(), tree[idx].end(), x);
        int m = (s + e) / 2;
        return query(l, r, x, y, s, m, 2*idx) + query(l, r, x, y, m+1, e, 2*idx+1);
    }
};

struct Comparator {
    const vector<int>& group;
    int t;
    Comparator(const vector<int>& _group, int _t) : group(_group), t(_t) {}
    bool operator () (int i, int j) {
        if(group[i] != group[j]) return group[i] < group[j];
        return group[i+t] < group[j+t];
    }
};

vector<int> getSA(const string& s)
{
    int n = s.size();

    int t = 1;
    vector<int> group(n+1);
    for(int i = 0; i < n; i++) group[i] = s[i];
    group[n] = -1;

    vector<int> perm(n);
    for(int i = 0; i < n; i++) perm[i] = i;
    while(t < n) {
        auto compareUsing2T = Comparator(group, t);
        sort(perm.begin(), perm.end(), compareUsing2T);

        t *= 2;
        if(t >= n) break;

        vector<int> newGroup(n+1);
        newGroup[perm[0]] = 0;
        newGroup[n] = -1;
        for(int i = 1; i < n; i++) {
            newGroup[perm[i]] = newGroup[perm[i-1]] + compareUsing2T(perm[i-1], perm[i]);
        }
        group = newGroup;
    }
    return perm;
}

vector<int> getLCP(const string& s, const vector<int>& sa)
{
    int n = s.size();
    vector<int> isa(n);
    for(int i = 0; i < n; i++) isa[sa[i]] = i;
    vector<int> lcp(n);
    for(int i = 0, k = 0; i < n; i++) {
        if(isa[i] == 0) continue;
        for(int j = sa[isa[i]-1]; s[i+k] == s[j+k]; k++);
        lcp[isa[i]] = k;
        k = max(k-1, 0);
    }
    return lcp;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n;
    cin >> n;
    string s;
    cin >> s;

    auto sa = getSA(s);
    auto lcp = getLCP(s, sa);
    vector<int> h(s.size()+1);
    for(int i = 0; i < n; i++) h[i+1] += s[i] == '(' ? +1 : -1;
    for(int i = 1; i <= n; i++) h[i] += h[i-1];
    Seg seg(h);
    MergeSortTree mst(h);
    int prv = -1;
    int ans = 0;
    for(int i = 0; i < n; i++) {
        int now = seg.Q(sa[i]+1, n, h[sa[i]]) - sa[i];
        int r = seg.first_lt(sa[i]+1, h[sa[i]])-1;
        ans += mst.Q(sa[i]+1, r, h[sa[i]], h[sa[i]]) - mst.Q(sa[i]+1, min(r, sa[i]+lcp[i]), h[sa[i]], h[sa[i]]);
        prv = now;
    }
    cout << ans;
}