#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10;
const int MAXM = 11;
const int MAXA = 11;

int N, M, l[MAXM], r[MAXM], c[MAXM];
vector<int> A;
map<vector<int>, int> dp;

int toidx(const vector<int>& a)
{
    int ret = 0;
    for(auto i : a) {
        ret *= 10;
        ret += i;
    }
    return ret;
}

int main()
{
    cin >> N;
    A.resize(N);
    for(int i = 0; i < N; i++) cin >> A[i];
    cin >> M;
    for(int i = 0; i < M; i++) {
        cin >> l[i] >> r[i] >> c[i];
        l[i]--; r[i]--;
    }

    priority_queue<pair<int, vector<int>>> pq;
    dp[A] = 0;
    pq.emplace(0, A);
    
    while(!pq.empty()) {
        auto [dist, a] = pq.top(); pq.pop();
        dist = -dist;
        if(dp.find(a) != dp.end() && dp[a] < dist) continue;

        for(int i = 0; i < M; i++) {
            swap(a[l[i]], a[r[i]]);

            if(dp.find(a) == dp.end() || dist + c[i] < dp[a]) {
                dp[a] = dist + c[i];
                pq.emplace(-dp[a], a);
            }

            swap(a[l[i]], a[r[i]]);
        }
    }

    sort(A.begin(), A.end());

    if(dp.find(A) == dp.end()) cout << -1;
    else cout << dp[A];
}