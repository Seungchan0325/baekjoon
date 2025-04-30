#include <bits/stdc++.h>

using namespace std;

const int MAXN = 202020;

int N, Q, ans[MAXN];
set<pair<int, int>> s[MAXN];

void merge(int a, int b)
{
    if(s[a].size() < s[b].size()) swap(s[a], s[b]), swap(ans[a], ans[b]);
    for(auto [l, r] : s[b]) {
        int mx = r;
        int mn = l;
        while(true) {
            auto it = s[a].lower_bound({l, 0});
            if(it == s[a].end()) break;
            if(it->first <= r) {
                ans[a] -= it->second - it->first + 1;
                
                mn = min(it->first, mn);
                mx = max(it->second, mx);
                s[a].erase(it);
            } else break;
        }
        while(true) {
            auto it = s[a].lower_bound({l, 0});
            if(it == s[a].begin()) break;
            it--;
            if(l <= it->second) {
                ans[a] -= it->second - it->first + 1;

                mn = min(it->first, mn);
                mx = max(it->second, mx);
                s[a].erase(it);
            } else break;
        }
        ans[a] += mx - mn + 1;
        s[a].emplace(mn, mx);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> Q;
    for(int i = 1; i <= N; i++) {
        int l, r; cin >> l >> r;
        ans[i] = r - l + 1;
        s[i].emplace(l, r);
    }

    while(Q--) {
        int op;
        cin >> op;

        if(op == 1) {
            int a, b;
            cin >> a >> b;
            merge(a, b);
        } else {
            int a;
            cin >> a;
            cout << ans[a] << "\n"; 
        }
    }
}