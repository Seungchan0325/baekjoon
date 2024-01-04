#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;
using ll = long long;

const int INF = INT_MAX;

int n, h[500001];
stack<pii> s;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n;
    for(int i = 0; i < n; i++) cin>>h[i];

    ll sum = 0;
    s.push({INF, -1});
    for(int i = 0; i < n; i++) {
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