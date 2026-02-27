#include <bits/stdc++.h>

using namespace std;

const int MAXN = 202020;

struct Node {
    uint A, O, mx, lzA, lzO;
};

int N, M, A[MAXN];
Node tree[4*MAXN];

void apply_and(int s, int e, int idx, uint v)
{
    tree[idx].lzO &= v;
    tree[idx].lzA &= v;
    tree[idx].A &= v;
    tree[idx].O &= v;
    tree[idx].mx &= v;
}

void apply_or(int s, int e, int idx, uint v)
{
    tree[idx].lzO |= v;
    tree[idx].lzA |= v;
    tree[idx].A |= v;
    tree[idx].O |= v;
    tree[idx].mx |= v;
}

void push(int s, int e, int idx)
{
    if(s != e) {
        int m = (s + e) / 2;
        apply_and(s, m, 2*idx, tree[idx].lzA);
        apply_or(s, m, 2*idx, tree[idx].lzO);
        apply_and(m+1, e, 2*idx+1, tree[idx].lzA);
        apply_or(m+1, e, 2*idx+1, tree[idx].lzO);
    }
    tree[idx].lzA = 0xffffffffu;
    tree[idx].lzO = 0x00000000u;
}

void pull(int s, int e, int idx)
{
    tree[idx].A = tree[2*idx].A & tree[2*idx+1].A;
    tree[idx].O = tree[2*idx].O | tree[2*idx+1].O;
    tree[idx].mx = max(tree[2*idx].mx, tree[2*idx+1].mx);
}

void init(int s = 1, int e = N, int idx = 1)
{
    tree[idx].lzA = 0xffffffffu;
    tree[idx].lzO = 0x00000000u;
    if(s == e) {
        tree[idx].A = tree[idx].O = tree[idx].mx = A[s];
        return;
    }
    int m = (s + e) / 2;
    init(s, m, 2*idx);
    init(m+1, e, 2*idx+1);
    pull(s, e, idx);
}

void update_and(int l, int r, uint v, int s = 1, int e = N, int idx = 1)
{
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        if(((~v&~tree[idx].O) | (~v&tree[idx].A)) == ~v) {
            apply_and(s, e, idx, v);
            return;
        }
    }
    int m = (s + e) / 2;
    push(s, e, idx);
    update_and(l, r, v, s, m, 2*idx);
    update_and(l, r, v, m+1, e, 2*idx+1);
    pull(s, e, idx);
}

void update_or(int l, int r, uint v, int s = 1, int e = N, int idx = 1)
{
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        if(((v&~tree[idx].O) | (v&tree[idx].A)) == v) {
            apply_or(s, e, idx, v);
            return;
        }
    }
    int m = (s + e) / 2;
    push(s, e, idx);
    update_or(l, r, v, s, m, 2*idx);
    update_or(l, r, v, m+1, e, 2*idx+1);
    pull(s, e, idx);
}

uint query(int l, int r, int s = 1, int e = N, int idx = 1)
{
    if(e < l || r < s) return 0;
    if(l <= s && e <= r) return tree[idx].mx;
    int m = (s + e) / 2;
    push(s, e, idx);
    return max(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i];
    init();
    cin >> M;
    while(M--) {
        int t, l, r;
        cin >> t >> l >> r;
        if(t == 1) {
            uint x;
            cin >> x;
            update_and(l, r, x);
        } else if(t == 2) {
            uint x;
            cin >> x;
            update_or(l, r, x);
        } else if(t == 3) {
            uint ans = query(l, r);
            cout << ans << "\n";
        }
    }
}