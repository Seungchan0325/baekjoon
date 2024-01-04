#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct P {
    int t;
    ll u;
    ll den;    //분모

    bool operator<(const P& other) {
        return u * other.den > other.u * den;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    ll n, k, a[4];
    vector<ll> cards[4];
    cin>>n>>k;
    for(int i=0; i<4; i++) cin>>a[i];
    for(int i=0; i<n; i++) {
        char t;
        int u;
        cin>>t>>u;
        t-='A';
        cards[t].push_back(u);
    }

    vector<P> v;
    for(int i=0; i<4; i++) {
        sort(cards[i].begin(), cards[i].end(), greater<>());
        ll p = a[i];
        for(auto u : cards[i]) {
            v.push_back({i, u, p});
            p += u;
        }
    }

    sort(v.begin(), v.end());
    for(int i=0; i<k; i++) {
        int t = v[i].t;
        int u = v[i].u;
        cout<<"ABCD"[t]<<" "<<u<<"\n";
    }
}