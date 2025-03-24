#include <bits/stdc++.h>

using namespace std;

const int MAXN = 202020;

int N, tree[4*MAXN];

void init(int s = 0, int e = N-1, int idx = 1)
{
    tree[idx] = 0;
    if(s == e) return;
    int m = (s + e) / 2;
    init(s, m, 2*idx);
    init(m+1, e, 2*idx+1);
}

void update(int x, int v, int s = 0, int e = N-1, int idx = 1)
{
    if(e < x || x < s) return;
    if(s == e) {
        tree[idx] = max(tree[idx], v);
        return;
    }
    int m = (s + e) / 2;
    update(x, v, s, m, 2*idx);
    update(x, v, m+1, e, 2*idx+1);
    tree[idx] = max(tree[2*idx], tree[2*idx+1]);
}

int query(int l, int r, int s = 0, int e = N-1, int idx = 1)
{
    if(e < l || r < s) return 0;
    if(l <= s && e <= r) return tree[idx];
    int m = (s + e) / 2;
    return max(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
}

vector<int> get_lis(vector<int> v)
{
    int n = v.size();
    vector<int> dp, lis(n);
    int j = 0;
    for(int i = 0; i < n; i++) {
        j = max(i + 1, j);
        while(j < n && v[j-1] < v[j]) j++;
        lis[i] = j - i;
    }
    return lis;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int z;
    cin >> z;
    while(z--) {
        cin >> N;
        vector<int> v(N);
        for(auto& i : v) cin >> i;
        auto rv = v;

        vector<int> vlis(N), rvlis(N);

        int j = N-1;
        for(int i = N-1; i >= 0; i--) {
            j = min(j, i-1);
            while(j >= 0 && v[j] < v[j+1]) j--;
            vlis[i] = i-j;
        }

        j = 0;
        for(int i = 0; i < N; i++) {
            j = max(j, i+1);
            while(j < N && v[j-1] < v[j]) j++;
            rvlis[i] = j-i;
        }

        vector<tuple<int, int, int>> upd, rupd;
        for(int i = 0; i < N; i++) {
            upd.emplace_back(v[i], i, vlis[i]);
            rupd.emplace_back(rv[i], i, rvlis[i]);
        }
        sort(upd.begin(), upd.end(), greater<>());
        sort(rupd.begin(), rupd.end(), greater<>());

        init();

        j = 0;
        int ans = 0;
        for(auto [vi, i, lis] : upd) {
            while(j < N && get<0>(rupd[j]) > vi) {
                auto [vj, ji, jlis] = rupd[j];
                update(ji, jlis);
                j++;
            }
            ans = max(ans, lis + query(i, N-1));
        }

        cout << ans << "\n";
    }
}