#include "nile.h"

#include "grader.cpp"

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

std::vector<long long> calculate_costs(std::vector<int> W, std::vector<int> A,
                                       std::vector<int> B, std::vector<int> E) {
    int N = W.size();
    int Q = (int)E.size();
    std::vector<long long> R(Q, 0);

    vector<tuple<int, int, int>> jobs;
    for(int i = 0; i < N; i++) {
        jobs.emplace_back(W[i], A[i], B[i]);
    }
    sort(jobs.begin(), jobs.end());
    for(int i = 0; i < N; i++) {
        tie(W[i], A[i], B[i]) = jobs[i];
    }
    
    for(int i = 0; i < Q; i++) {
        vector<ll> dp(N);
        dp[0] = A[0];
        for(int j = 1; j < N; j++) {
            dp[j] = dp[j-1] + A[j];
            if(j-1 >= 0 && W[j] - W[j-1] <= E[i]) {
                if(j-2 < 0) dp[j] = min<ll>(dp[j], (ll)B[j-1] + B[j]);
                else dp[j] = min(dp[j], dp[j-2] + (ll)B[j-1] + B[j]);
            }
            if(j-2 >= 0 && W[j] - W[j-2] <= E[i]) {
                if(j-3 < 0) dp[j] = min<ll>(dp[j], (ll)A[j-1] + B[j-2] + B[j]);
                else dp[j] = min(dp[j], dp[j-3] + (ll)A[j-1] + B[j-2] + B[j]);
            }
        }
        R[i] = dp[N-1];
    }
    return R;
}
