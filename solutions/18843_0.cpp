#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;
const int MAXM = 303030;

long long ans;
long long N, M, A[MAXM], B[MAXM], par[MAXN], sz[MAXN];
set<int> in[MAXN], out[MAXN];
set<pair<int, int>> ine[MAXN], oute[MAXN];

int find(int x)
{
    if(par[x] == x) return x;
    return par[x] = find(par[x]);
}

void merge(int x, int y)
{
    x = find(x);
    y = find(y);
    if(x == y) return;
    if(sz[x] < sz[y]) swap(x, y);

    out[x].erase(y);
    in[x].erase(y);
    out[y].erase(x);
    out[y].erase(x);
    vector<int> v;
    for(auto i : in[y]) {
        out[find(i)].erase(y);
        out[find(i)].insert(x);
        if(out[x].contains(i)) v.push_back(i);
    }
    for(auto i : out[y]) {
        in[find(i)].erase(y);
        in[find(i)].insert(x);
        if(in[x].contains(i)) v.push_back(i);
    }
    in[x].insert(in[y].begin(), in[y].end());
    out[x].insert(out[y].begin(), out[y].end());

    ans -= sz[x] * (sz[x] - 1);
    ans -= sz[y] * (sz[y] - 1);
    ans -= sz[x] * ine[x].size();
    ans -= sz[y] * ine[y].size();

    for(auto [a, b] : ine[y]) {
        if(find(a) == x) {
            oute[find(b)].erase({a, b});
        } else {
            assert(b == y);
            ine[x].insert({a, x});
            oute[find(a)].erase({a, b});
            oute[find(a)].insert({a, x});
        }
    }

    for(auto [a, b] : oute[y]) {
        if(find(b) == x) {
            ine[x].erase({a, b});
        } else {
            assert(find(a) == y);
            oute[x].insert({a, b});
        }
    }

    sz[x] += sz[y];
    ans += sz[x] * (sz[x] - 1);
    ans += sz[x] * ine[x].size();
    par[y] = x;

    for(auto i : v) merge(x, i);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    for(int i = 1; i <= M; i++) cin >> A[i] >> B[i];
    for(int i = 1; i <= N; i++) sz[i] = 1, par[i] = i;
    for(int i = 1; i <= M; i++) {
        out[find(A[i])].insert(find(B[i]));
        in[find(B[i])].insert(find(A[i]));
        if(find(A[i]) != find(B[i]) && !ine[find(B[i])].contains({A[i], find(B[i])})) {
            ine[find(B[i])].emplace(A[i], find(B[i]));
            oute[find(A[i])].emplace(A[i], find(B[i]));
            ans += sz[find(B[i])];
        }
        int x = find(A[i]);
        if(in[x].contains(find(B[i])) && out[x].contains(find(B[i]))) {
            merge(A[i], B[i]);
        }

        cout << ans << "\n";
    }
}