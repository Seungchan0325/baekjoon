#include <bits/stdc++.h>

using namespace std;

// #define int long long

const int MAXN = 505050;
const int inf = 2e9+1e8;

struct Node {
    int mn, smn, mx, smx, histmn, histmx, lzadd, lzaddmn, lzaddmx, lzmndw, lzmnup, lzmxdw, lzmxup;
};

int N, M, A[MAXN];
Node tree[4*MAXN];

void apply(int s, int e, int ch, int par)
{
    tree[ch].mn += tree[par].lzadd;
    tree[ch].mx += tree[par].lzadd;
    if(tree[ch].smn < inf) tree[ch].smn += tree[par].lzadd;
    if(tree[ch].smx > -inf) tree[ch].smx += tree[par].lzadd;
    tree[ch].lzaddmn = min(tree[ch].lzaddmn, tree[ch].lzadd + tree[par].lzaddmn);
    tree[ch].lzaddmx = max(tree[ch].lzaddmx, tree[ch].lzadd + tree[par].lzaddmx);
    tree[ch].lzadd += tree[par].lzadd;

    bool mnUpd = false;
    bool mxUpd = false;
    if(tree[ch].mn < tree[par].mn) {
        mnUpd = true;
        if(tree[ch].mn == tree[ch].mx) {
            mxUpd = true;
            tree[ch].mx = tree[par].mn;
            tree[ch].lzmxdw = min(tree[ch].lzmxdw, tree[par].lzmndw);
            tree[ch].lzmxup = max(tree[ch].lzmxup, tree[par].lzmnup);
        }
        else if(tree[ch].mn == tree[ch].smx)
            tree[ch].smx = tree[par].mn;
        tree[ch].mn = tree[par].mn;
        tree[ch].lzmndw = min(tree[ch].lzmndw, tree[par].lzmndw);
        tree[ch].lzmnup = max(tree[ch].lzmnup, tree[par].lzmnup);
    }

    if(tree[ch].mx > tree[par].mx) {
        mxUpd = true;
        if(tree[ch].mx == tree[ch].mn) {
            mnUpd = true;
            tree[ch].mn = tree[par].mx;
            tree[ch].lzmndw = min(tree[ch].lzmndw, tree[par].lzmxdw);
            tree[ch].lzmnup = max(tree[ch].lzmnup, tree[par].lzmxup);
        }
        if(tree[ch].mx == tree[ch].smn)
            tree[ch].smn = tree[par].mx;
        tree[ch].mx = tree[par].mx;
        tree[ch].lzmxdw = min(tree[ch].lzmxdw, tree[par].lzmxdw);
        tree[ch].lzmxup = max(tree[ch].lzmxup, tree[par].lzmxup);
    }

    if(mnUpd == false) {
        tree[ch].lzmndw = min(tree[ch].lzmndw, tree[ch].mn - tree[par].lzadd + tree[par].lzaddmn);
        tree[ch].lzmnup = max(tree[ch].lzmnup, tree[ch].mn - tree[par].lzadd + tree[par].lzaddmx);
    }
    if(mxUpd == false) {
        tree[ch].lzmxdw = min(tree[ch].lzmxdw, tree[ch].mx - tree[par].lzadd + tree[par].lzaddmn);
        tree[ch].lzmxup = max(tree[ch].lzmxup, tree[ch].mx - tree[par].lzadd + tree[par].lzaddmx);
    }
    tree[ch].histmn = min(tree[ch].histmn, tree[ch].lzmndw);
    tree[ch].histmx = max(tree[ch].histmx, tree[ch].lzmnup);
    tree[ch].histmn = min(tree[ch].histmn, tree[ch].lzmxdw);
    tree[ch].histmx = max(tree[ch].histmx, tree[ch].lzmxup);
}
void push(int s, int e, int idx)
{
    if(s != e) {
        int m = (s + e) / 2;
        apply(s, m, 2*idx, idx);
        apply(m+1, e, 2*idx+1, idx);
    }
    tree[idx].lzadd = tree[idx].lzaddmn = tree[idx].lzaddmx = 0;
    tree[idx].lzmndw = tree[idx].lzmnup = tree[idx].mn;
    tree[idx].lzmxdw = tree[idx].lzmxup = tree[idx].mx;
}
void pull(int s, int e, int idx)
{
    if(tree[2*idx].mn < tree[2*idx+1].mn) {
        tree[idx].mn = tree[2*idx].mn;
        tree[idx].smn = min(tree[2*idx].smn, tree[2*idx+1].mn);
    } else if(tree[2*idx+1].mn < tree[2*idx].mn) {
        tree[idx].mn = tree[2*idx+1].mn;
        tree[idx].smn = min(tree[2*idx+1].smn, tree[2*idx].mn);
    } else {
        tree[idx].mn = tree[2*idx].mn;
        tree[idx].smn = min(tree[2*idx].smn, tree[2*idx+1].smn);
    }

    if(tree[2*idx].mx > tree[2*idx+1].mx) {
        tree[idx].mx = tree[2*idx].mx;
        tree[idx].smx = max(tree[2*idx].smx, tree[2*idx+1].mx);
    } else if(tree[2*idx+1].mx > tree[2*idx].mx) {
        tree[idx].mx = tree[2*idx+1].mx;
        tree[idx].smx = max(tree[2*idx+1].smx, tree[2*idx].mx);
    } else {
        tree[idx].mx = tree[2*idx].mx;
        tree[idx].smx = max(tree[2*idx].smx, tree[2*idx+1].smx);
    }

    tree[idx].lzmndw = tree[idx].lzmnup = tree[idx].mn;
    tree[idx].lzmxdw = tree[idx].lzmxup = tree[idx].mx;
    tree[idx].histmn = min(tree[2*idx].histmn, tree[2*idx+1].histmn);
    tree[idx].histmx = max(tree[2*idx].histmx, tree[2*idx+1].histmx);
}
void init(int s = 1, int e = N, int idx = 1)
{
    if(s == e) {
        tree[idx].mn = tree[idx].mx = tree[idx].histmn = tree[idx].histmx = tree[idx].lzmndw = tree[idx].lzmnup = tree[idx].lzmxdw = tree[idx].lzmxup = A[s];
        tree[idx].smn = inf;
        tree[idx].smx = -inf;
        tree[idx].lzadd = tree[idx].lzaddmn = tree[idx].lzaddmx = 0;
        return;
    }
    int m = (s + e) / 2;
    init(s, m, 2*idx);
    init(m+1, e, 2*idx+1);
    pull(s, e, idx);
}
void add(int l, int r, int v, int s = 1, int e = N, int idx = 1)
{
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        tree[idx].mn += v;
        tree[idx].mx += v;
        if(tree[idx].smn < inf) tree[idx].smn += v;
        if(tree[idx].smx > -inf) tree[idx].smx += v;
        tree[idx].lzadd += v;
        tree[idx].lzaddmn = min(tree[idx].lzaddmn, tree[idx].lzadd);
        tree[idx].lzaddmx = max(tree[idx].lzaddmx, tree[idx].lzadd);
        tree[idx].lzmndw = min(tree[idx].lzmndw, tree[idx].mn);
        tree[idx].lzmnup = max(tree[idx].lzmnup, tree[idx].mn);
        tree[idx].lzmxdw = min(tree[idx].lzmxdw, tree[idx].mx);
        tree[idx].lzmxup = max(tree[idx].lzmxup, tree[idx].mx);
        tree[idx].histmn = min(tree[idx].histmn, tree[idx].mn);
        tree[idx].histmx = max(tree[idx].histmx, tree[idx].mx);
        return;
    }
    int m = (s + e) / 2;
    push(s, e, idx);
    add(l, r, v, s, m, 2*idx);
    add(l, r, v, m+1, e, 2*idx+1);
    pull(s, e, idx);
}
void chmax(int l, int r, int v, int s = 1, int e = N, int idx = 1)
{
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        if(tree[idx].mn >= v) return;
        if(tree[idx].smn > v) {
            if(tree[idx].mn == tree[idx].mx) {
                tree[idx].mx = v;
                tree[idx].lzmxup = max(tree[idx].lzmxup, v);
            }
            else if(tree[idx].mn == tree[idx].smx)
                tree[idx].smx = v;
            tree[idx].mn = v;
            tree[idx].lzmnup = max(tree[idx].lzmnup, v);
            tree[idx].histmx = max(tree[idx].histmx, tree[idx].lzmnup);
            return;
        }
    }
    int m = (s + e) / 2;
    push(s, e, idx);
    chmax(l, r, v, s, m, 2*idx);
    chmax(l, r, v, m+1, e, 2*idx+1);
    pull(s, e, idx);
}
void chmin(int l, int r, int v, int s = 1, int e = N, int idx = 1)
{
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        if(tree[idx].mx <= v) return;
        if(tree[idx].smx < v) {
            if(tree[idx].mx == tree[idx].mn) {
                tree[idx].mn = v;
                tree[idx].lzmndw = min(tree[idx].lzmndw, v);
            }
            else if(tree[idx].mx == tree[idx].smn)
                tree[idx].smn = v;
            tree[idx].mx = v;
            tree[idx].lzmxdw = min(tree[idx].lzmxdw, v);
            tree[idx].histmn = min(tree[idx].histmn, tree[idx].lzmxdw);
            return;
        }
    }
    int m = (s + e) / 2;
    push(s, e, idx);
    chmin(l, r, v, s, m, 2*idx);
    chmin(l, r, v, m+1, e, 2*idx+1);
    pull(s, e, idx);
}
int QA(int l, int r, int s = 1, int e = N, int idx = 1)
{
    if(e < l || r < s) return inf;
    if(l <= s && e <= r) return tree[idx].mn;
    int m = (s + e) / 2;
    push(s, e, idx);
    return min(QA(l, r, s, m, 2*idx), QA(l, r, m+1, e, 2*idx+1));
}
int QB(int l, int r, int s = 1, int e = N, int idx = 1)
{
    if(e < l || r < s) return inf;
    if(l <= s && e <= r) return tree[idx].histmn;
    int m = (s + e) / 2;
    push(s, e, idx);
    return min(QB(l, r, s, m, 2*idx), QB(l, r, m+1, e, 2*idx+1));
}
int QC(int l, int r, int s = 1, int e = N, int idx = 1)
{
    if(e < l || r < s) return -inf;
    if(l <= s && e <= r) return tree[idx].histmx;
    int m = (s + e) / 2;
    push(s, e, idx);
    return max(QC(l, r, s, m, 2*idx), QC(l, r, m+1, e, 2*idx+1));
}

signed main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i];
    cin >> M;

    init();
    while(M--) {    
        int t, l, r;
        cin >> t >> l >> r;
        switch(t) {
            case 1:
            {
                int x;
                cin >> x;
                add(l, r, x);
            }
            break;
            case 2:
            {
                int y;
                cin >> y;
                chmax(l, r, y);
            }
            break;
            case 3:
            {
                int y;
                cin >> y;
                chmin(l, r, y);
            }
            break;
            case 4:
            {
                int ans = QA(l, r);
                cout << ans << "\n";
            }
            break;
            case 5:
            {
                int ans = QB(l, r);
                cout << ans << "\n";
            }
            break;
            case 6:
            {
                int ans = QC(l, r);
                cout << ans << "\n";
            }
            break;
            default:
            assert(0);
            break;
        }
    }
}