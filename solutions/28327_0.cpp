#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 200005;

ll n, arr[MAXN], rarr[MAXN], dir[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n;
    for(ll i = 1; i <= n; i++) {
        cin >> arr[i];
        rarr[arr[i]] = i;
    }

    ll g = 0;
    set<ll> s;
    for(ll i = 1; i <= n; i++) {
        ll idx = rarr[i];
        auto it = s.lower_bound(idx);
        ll pprv = -1;
        ll prv = -1;
        ll nxt = -1;
        ll nnxt = -1;
        if(it != s.begin()) {
            it--;
            if(it != s.begin()) {
                it--;
                pprv = *it;
                it++;
            }
            prv = *it;
            it++;
        }
        if(it != s.end()) {
            nxt = *it;
            it++;
            if(it != s.end()) {
                nnxt = *it;
            }
            it--;
        }
        s.insert(idx);

        vector<ll> v;
        for(auto j : {pprv, prv, nxt, nnxt})
            if(j != -1) v.push_back(j);

        for(ll j = 0; j + 2 < v.size(); j++) {
            if((arr[v[j]] < arr[v[j+1]]) == (arr[v[j+1]] < arr[v[j+2]])) {
                g += v[j] * (n - v[j+2] + 1);
            }
        }

        g += idx * (n - idx + 1);

        v.clear();
        for(auto j : {pprv, prv, idx, nxt, nnxt})
            if(j != -1) v.push_back(j);
        
        for(ll j = 0; j + 2 < v.size(); j++) {
            if((arr[v[j]] < arr[v[j+1]]) == (arr[v[j+1]] < arr[v[j+2]])) {
                g -= v[j] * (n - v[j+2] + 1);
            }
        }
        cout << g << "\n";
    }
}