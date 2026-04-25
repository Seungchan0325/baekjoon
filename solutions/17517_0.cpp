#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 250505;

ll N, S[MAXN], E[MAXN], V[MAXN];
vector<int> g[MAXN];
priority_queue<ll> pq[MAXN];

void dfs(int u)
{
    for(auto v : g[u]) {
        dfs(v);
        if(pq[u].size() < pq[v].size()) swap(pq[u], pq[v]);
        vector<ll> tmp;
        while(pq[v].size()) {
            tmp.push_back(pq[v].top()+pq[u].top());
            pq[v].pop(); pq[u].pop();
        }
        for(ll i : tmp) pq[u].push(i);
    }
    pq[u].push(V[u]);
}

int main()
{
    cin >> N;
    S[0] = 0;
    E[0] = 1e6 + 1;
    for(int i = 1; i <= N; i++) cin >> S[i] >> E[i] >> V[i];
    vector<int> v(N);
    iota(v.begin(), v.end(), 1);
    sort(v.begin(), v.end(), [](int i, int j) { return pair(S[i], -E[i]) < pair(S[j], -E[j]); });
    stack<int> st; st.push(0);
    for(auto i : v) {
        while(E[st.top()] <= S[i]) st.pop();
        g[st.top()].push_back(i);
        st.push(i);
    }
    dfs(0);
    ll sum = 0;
    for(int i = 1; i <= N; i++) {
        if(pq[0].size()) sum += pq[0].top(), pq[0].pop();
        cout << sum << "\n";
    }
}
