#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

int n, q, A[MAXN], tree[2*MAXN];

void update(int pos, int value)
{
    for(tree[pos += n] = value; pos > 1; pos >>= 1) {
        tree[pos>>1] = tree[pos] + tree[pos^1];
    }
}

int query(int l, int r)
{
    int ret = 0;
    for(l += n, r += n; l <= r; l >>= 1, r >>= 1) {
        if(l&1) ret += tree[l++];
        if(~r&1) ret += tree[r--];
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> q;
    for(int i = 1; i <= n; i++) {
        cin >> A[i];
    }

    for(int i = 1; i <= n; i++) {
        if(A[i] != A[i+1]) update(i, 1);
    }

    while(q--) {
        int t;
        cin >> t;
        if(t == 1) {
            int i, x;
            cin >> i >> x;
            A[i] = x;
            update(i, A[i] == A[i+1] ? 0 : 1);
            i--;
            update(i, A[i] == A[i+1] ? 0 : 1);
        } else {
            int l, r;
            cin >> l >> r;
            int result = query(l, r);
            if(A[r] == A[r+1]) result++;
            cout << result << "\n";
        }
    }
}