#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

struct DSU {
    vector<int> root;

    void init(int N)
    {
        root.resize(N);
        iota(root.begin(), root.end(), 0);
    }

    int find(int x)
    {
        if(root[x] == x) return x;
        return root[x] = find(root[x]);
    }

    void merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        root[y] = x;
    }
};

int N, L, H[MAXN], W[MAXN], DP[MAXN];
stack<int> s;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
deque<pair<int, int>> dq;
DSU dsu;

int solve(int L)
{
    while(s.size()) s.pop();
    while(pq.size()) pq.pop();
    while(dq.size()) dq.pop_back();
    dsu.init(N+1);
    s.push(0);
    dq.push_back({0, 0});
    pq.push({0, 0});
    auto C = [&](int i) {
        return DP[i] + H[dsu.find(i+1)];
    };
    for(int i = 1; i <= N; i++) {
        while(s.size() && H[s.top()] <= H[i]) {
            dsu.merge(i, s.top());
            s.pop();
        }
        s.push(i);
        
        int lo = -1;
        int hi = dq.size();
        while(lo+1<hi) {
            int mid = (lo+hi)/2;
            if(dsu.find(dq[mid].second+1) == i) hi = mid;
            else lo = mid;
        }
        pq.push({C(dq[hi].second), dq[hi].second});
        
        while(W[i]-W[dq.front().second] > L) dq.pop_front();
        pq.push({C(dq[0].second), dq[0].second});
        while(pq.top().first != C(pq.top().second) || W[i]-W[pq.top().second] > L) pq.pop();
        DP[i] = pq.top().first;
        while(dq.size() && dq.back().first > DP[i]) dq.pop_back();
        dq.push_back({DP[i], i});
    }
    return DP[N];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> W[i] >> H[i];

    int mx = *max_element(W+1, W+N+1);

    for(int i = 1; i <= N; i++) W[i] += W[i-1];

    int lo = mx;
    int hi = 1e7;
    while(lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if(solve(mid) > mid) lo = mid;
        else hi = mid;
    }
    int ans = min(max(lo, solve(lo)), max(hi, solve(hi)));
    cout << ans << "\n";
}