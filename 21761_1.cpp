#include <bits/stdc++.h>

using namespace std;

struct P {
    int t;
    int u;
    int den;    //분모

    bool operator<(const P& other) {
        return u * other.den > other.u * den;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, k, a[4];
    vector<int> cards[4];
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
        int p = a[i];
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