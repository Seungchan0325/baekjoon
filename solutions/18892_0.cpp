#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 9;
const int MAXN = 505;

int N, K, A[MAXN], cache1[MAXN], cache2[MAXN];

int lis(int i)
{
    int& ret = cache1[i];
    if(ret != -1) return ret;
    ret = 1;
    for(int j = i+1; j <= N; j++) {
        if(A[i] < A[j]) ret = max(ret, lis(j) + 1);
    }
    return ret;
}

int dp(int i)
{
    if(lis(i) == 1) return 1;
    int& ret = cache2[i];
    if(ret != -1) return ret;
    ret = 0;
    for(int j = i+1; j <= N; j++) {
        if(A[i] < A[j] && lis(j) + 1 == lis(i)) ret += dp(j), ret = min(ret, INF);
    }
    return ret;
}

void find(int i, int k)
{
    if(i != 0) cout << A[i] << " ";
    vector<pair<int, int>> a;
    for(int j = i+1; j <= N; j++) if(A[i] < A[j] && lis(j) + 1 == lis(i)) a.emplace_back(A[j], j);
    sort(a.begin(), a.end());
    for(auto [_, j] : a) {
        if(k - dp(j) <= 0) {
            find(j, k);
            return;
        }
        k -= dp(j);
    }
    // assert(0);
}

int main()
{
    cin >> N >> K;
    for(int i = 1; i <= N; i++) cin >> A[i];
    memset(cache1, -1, sizeof(cache1));
    memset(cache2, -1, sizeof(cache2));
    if(dp(0) < K) cout << "-1";
    else find(0, K);
}