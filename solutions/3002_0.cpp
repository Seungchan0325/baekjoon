#include <bits/stdc++.h>

using namespace std;

const int MAXN = 250505;

struct T {
    int over = 0;
    int sum = 0;
    int count[10] = {0, };
};


int N, M, lazy[4*MAXN];
T tree[4*MAXN];

T merge(T a, T b)
{
    T ret;
    ret.sum = a.sum + b.sum;
    ret.over = a.over + b.over;
    for(int i = 0; i < 10; i++) ret.count[i] = a.count[i] + b.count[i];
    return ret;
}

void propagate(int s, int e, int idx)
{
    if(lazy[idx]) {
        tree[idx].sum += (e - s + 1) * lazy[idx];
        for(int i = 0; i < 10; i++) {
            tree[idx].over += tree[idx].count[i] * ((i+lazy[idx])/10);
        }
        rotate(tree[idx].count, tree[idx].count+10-lazy[idx]%10, tree[idx].count+10);

        if(s != e) {
            lazy[2*idx] += lazy[idx];
            lazy[2*idx+1] += lazy[idx];
        }
        lazy[idx] = 0;
    }
}

void init(int s = 1, int e = N, int idx = 1)
{
    if(s == e) {
        tree[idx].count[0] = 1;
        return;
    }
    int m = (s + e) / 2;
    init(s, m, 2*idx);
    init(m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}


void update(int l, int r, int x, int s = 1, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return;
    if(l <= s && e <= r) {
        lazy[idx] += x;
        propagate(s, e, idx);
        return;
    }
    int m = (s + e) / 2;
    update(l, r, x, s, m, 2*idx);
    update(l, r, x, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

T query(int l, int r, int s = 1, int e = N, int idx = 1)
{
    propagate(s, e, idx);
    if(e < l || r < s) return T();
    if(l <= s && e <= r) return tree[idx];
    int m = (s + e) / 2;
    return merge(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    init();
    for(int i = 1; i <= N; i++) {
        char c; cin >> c;
        update(i, i, c-'0');
    }
    while(M--) {
        int A, B;
        cin >> A >> B;
        auto t = query(A, B);
        int ans = t.sum - 10 * t.over;
        cout << ans << "\n";
        update(A, B, 1);
    }
}