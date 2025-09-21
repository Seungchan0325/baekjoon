#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<ll, ll>;

const ll INF = 1e18;

ll n, h[500001];
stack<pii> s;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n;
    for(ll i = 0; i < n; i++) cin>>h[i];

    ll sum = 0;
    s.push({INF, -1});
    for(ll i = 0; i < n; i++) {
        while(s.top().first < h[i]) {
            sum += s.top().second;
            s.pop();
        }

        pii push = {h[i], 1};
        if(s.top().first == h[i]) {
            sum += s.top().second;
            push.second += s.top().second;
            s.pop();
        }
        if(s.top().first != INF) sum++;

        s.push(push);
    }
    cout<<sum;
}