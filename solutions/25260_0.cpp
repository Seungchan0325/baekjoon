#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;
const int LOGN = 20;

int N, Q, S[MAXN], E[MAXN], sparse[MAXN][LOGN+1], tree[4*MAXN];

int merge(int i, int j)
{
    if(i == 0 || j == 0) return i == 0 ? j : i;
    if(S[i] < S[j]) return i;
    return j;
}

void update(int v, int x, int s = 0, int e = N, int idx = 1)
{
    if(e < x || x < s) return;
    if(s == e) {
        tree[idx] = merge(tree[idx], v);
        return;
    }
    int m = (s + e) / 2;
    update(v, x, s, m, 2*idx);
    update(v, x, m+1, e, 2*idx+1);
    tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

int query(int l, int r, int s = 0, int e = N, int idx = 1)
{
    if(e < l || r < s) return 0;
    if(l <= s && e <= r) return tree[idx];
    int m = (s + e) / 2;
    return merge(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> Q;
    vector<int> v;
    v.reserve(N);
    for(int i = 1; i <= N; i++) {
        cin >> S[i] >> E[i];
        v.push_back(E[i]);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    for(int i = 1; i <= N; i++) {
        int idx = lower_bound(v.begin(), v.end(), E[i]) - v.begin();
        update(i, idx);
    }

    for(int i = 1; i <= N; i++) {
        int l = lower_bound(v.begin(), v.end(), S[i]) - v.begin();
        int r = lower_bound(v.begin(), v.end(), E[i]) - v.begin();
        int q = query(l, r);
        if(q != i) sparse[i][0] = q;
    }

    for(int j = 1; j <= LOGN; j++)
        for(int i = 1; i <= N; i++)
            sparse[i][j] = sparse[sparse[i][j-1]][j-1];
    
    while(Q--) {
        int s, e;
        cin >> s >> e;
        if(s == e) {
            cout << "0\n";
            continue;
        }
        // if(S[e] <= E[s] && E[s] <= S[e]) {
        //     cout << "1\n";
        //     continue;
        // }

        int ans = 0;
        for(int j = LOGN; j >= 0; j--) {
            if(sparse[e][j] != 0 && E[s] < S[sparse[e][j]]) {
                e = sparse[e][j];
                ans += 1<<j;
            }
        }

        if(E[s] < S[e]) e = sparse[e][0], ans++;
        if(e != s) ans++;

        if(S[e] <= E[s] && E[s] <= E[e]) cout << ans << "\n";
        else cout << "impossible\n";
    }
}