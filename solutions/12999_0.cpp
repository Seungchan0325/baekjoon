#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

int sqrtN;
struct Query {
    int l, r, idx;
    bool operator < (const Query& rhs) const {
        if(l/sqrtN != rhs.l/sqrtN) return l < rhs.l;
        return r < rhs.r;
    }
};

int n, q, a[MAXN], cnt[MAXN], ccnt[MAXN], mx;
vector<int> vs;

void push(int x)
{
    ccnt[cnt[x]]--;
    ccnt[++cnt[x]]++;
    mx = max(cnt[x], mx);
}

void pop(int x)
{
    --ccnt[cnt[x]];
    if(ccnt[mx] == 0) mx--;
    ccnt[--cnt[x]]++;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> q;
    sqrtN = sqrt(n);
    vs.push_back(-1e9);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        vs.push_back(a[i]);
    }
    sort(vs.begin(), vs.end());
    vs.erase(unique(vs.begin(), vs.end()), vs.end());
    for(int i = 1; i <= n; i++) {
        a[i] = lower_bound(vs.begin(), vs.end(), a[i]) - vs.begin();
    }

    vector<Query> Q(q);
    vector<int> ans(q);
    for(int i = 0; i < q; i++) {
        cin >> Q[i].l >> Q[i].r;
        Q[i].idx = i;
    }
    sort(Q.begin(), Q.end());

    for(int i = 0; i < vs.size(); i++) {
        ccnt[0]++;
    }

    int l = Q[0].l;
    int r = Q[0].l-1;
    for(int i = 0; i < q; i++) {
        while(l < Q[i].l) pop(a[l++]);
        while(Q[i].r < r) pop(a[r--]);
        while(Q[i].l < l) push(a[--l]);
        while(r < Q[i].r) push(a[++r]);
        ans[Q[i].idx] = mx;
    }
    for(int i = 0; i < q; i++) cout << ans[i] << "\n";
}