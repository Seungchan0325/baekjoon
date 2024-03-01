#include <bits/stdc++.h>

using namespace std;

struct T {
    int ret[6];
};

const int MAXN = 100005;

int N, Q;
T arr[MAXN];
T tree[4*MAXN];

T merge(const T& l, const T& r)
{
    T ret;
    for(int i = 1; i <= 5; i++) {
        ret.ret[i] = l.ret[r.ret[i]];
    }
    return ret;
}

void init(int s = 1, int e = N, int idx = 1)
{
    if(s == e) {
        tree[idx] = arr[s];
        return;
    }
    int m = (s + e) >> 1;
    init(s, m, 2*idx); init(m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

void update(int pos, const T& value, int s = 1, int e = N, int idx = 1)
{
    if(e < pos || pos < s) return;
    if(s == e) {
        tree[idx] = value;
        return;
    }

    int m = (s + e) >> 1;
    update(pos, value, s, m, 2*idx);
    update(pos, value, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

T query(int l, int r, int s = 1, int e = N, int idx = 1)
{
    if(e < l || r < s) return T{0, 1, 2, 3, 4, 5};
    if(l <= s && e <= r) return tree[idx];
    int m = (s + e) >> 1;
    return merge(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= 5; j++) {
            cin >> arr[i].ret[j];
        }
    }
    init();
    cin >> Q;
    while(Q--) {
        int u, a, b, y[6];
        cin >> u >> a >> b;
        for(int i = 1; i <= 5; i++) {
            cin >> y[i];
        }

        T l = query(a, u-1);
        T r = query(u+1, b);

        int inverse[6];
        for(int i = 1; i <= 5; i++) {
            inverse[l.ret[i]] = i;
        }

        T result;
        for(int i = 1; i <= 5; i++) {
            result.ret[r.ret[i]] = inverse[y[i]];
        }
        update(u, result);
        for(int i = 1; i <= 5; i++) {
            cout << result.ret[i] << " ";
        }
        cout << "\n";
    }
}