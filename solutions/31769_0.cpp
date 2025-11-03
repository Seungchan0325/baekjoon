#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 303030;

ll N, K, t[MAXN];
map<ll, vector<ll>> g;
map<ll, bool> pos;

int main()
{
    cin >> N >> K;
    for(int i = 1; i <= N; i++) cin >> t[i];

    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<>> pq;
    for(int i = 1; i <= K; i++) {
        pq.emplace(t[i], i);
    }
    for(int i = K+1; i <= N; i++) {
        auto top = pq.top(); pq.pop();
        pq.emplace(top.first+t[i], top.second);
        g[top.first+t[i]].push_back(top.first);
    }

    ll st = pq.top().first;
    cout << st << "\n";

    pos[st] = true;
    queue<ll> q;
    q.push(st);
    while(q.size()) {
        ll u = q.front(); q.pop();
        for(auto v : g[u]) {
            if(pos[v]) continue;
            pos[v] = true;
            q.push(v);
        }
    }
    for(int i = 1; i <= K; i++) cout << pos[t[i]];
    cout << "\n";
}