#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;
const int MAXQ = 200005;

int n, q, p[MAXN], parents[MAXN];
tuple<int, int, int> queries[MAXQ];

int find(int x) {
    if(parents[x] == x) return x;
    return parents[x] = find(parents[x]);
}

void Union(int x, int y) {
    x = find(x);
    y = find(y);
    parents[y] = x;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> q;
    for(int i = 2; i <= n; i++) cin >> p[i];
    q += n-1;
    for(int i = 0; i < q; i++) {
        auto& [t, a, b] = queries[i];
        cin >> t;
        if(t == 0) cin >> a;
        else cin >> a >> b;
    }

    for(int i = 1; i <= n; i++) parents[i] = i;

    stack<bool> ans;
    for(int i = q-1; i >= 0; i--) {
        auto [t, a, b] = queries[i];
        if(t == 0) Union(p[a], a);
        else {
            a = find(a);
            b = find(b);
            ans.push(a == b);
        }
    }

    while(!ans.empty()) {
        cout << (ans.top() ? "YES" : "NO") << "\n";
        ans.pop();
    }
}