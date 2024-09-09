#include <bits/stdc++.h>

using namespace std;

struct DSU {
    int N;
    vector<int> root;
    DSU(int _N) : N(_N) {
        root.resize(N+1);
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

const int MAXN = 100005;

int N, K, A[MAXN], PSUM[MAXN];
bool chk[MAXN];

signed main()
{
    cin >> N >> K;
    for(int i = 1; i <= N; i++) cin >> A[i];
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
    for(int i = 2; i <= N; i++) {
        PSUM[i] = PSUM[i-2] + A[i] - A[i-1];
        pq.emplace(A[i] - A[i-1], i-1, i);
    }
    DSU left(N+1), right(N+1);

    int ans = 0;
    while(K--) {
        while(!pq.empty()) {
            auto [cost, i, j] = pq.top(); pq.pop();
            if(chk[i] || chk[j]) continue;
            ans += cost;
            chk[i] = true;
            chk[j] = true;

            left.merge(i-1, i);
            left.merge(i, j);
            right.merge(j, i);
            right.merge(j+1, j);

            int l = left.find(i);
            int r = right.find(j);
            if(0 < l && r <= N) {
                pq.emplace(PSUM[r] - PSUM[l-1] - (PSUM[r-1] - PSUM[l]), l, r);
            }
            break;
        }
    }

    cout << ans;
}