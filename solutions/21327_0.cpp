#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;
const int INF = 987654321;

int N, M, K, B, cache[MAXN][MAXN];
vector<int> v[MAXN];

int f(int g, int remain)
{
    if(remain < 0) return -INF;
    if(g == 0) return 0;
    int& ret = cache[g][remain];
    if(ret != -1) return ret;

    ret = 0;
    int sum = 0;
    for(int i = 0; i < v[g].size(); i++) {
        ret = max(ret, f(g-1, remain - i) + sum);
        sum += v[g][i];
    }
    ret = max(ret, f(g-1, remain - v[g].size()) + sum + B);

    return ret;
}

int main()
{
    cin >> N >> M >> K >> B;
    for(int i = 0; i < N; i++) {
        int p, g;
        cin >> p >> g;
        v[g].push_back(p);
    }

    for(int i = 1; i <= M; i++) {
        sort(v[i].begin(), v[i].end(), greater<>());
    }

    memset(cache, -1, sizeof(cache));
    int ans = f(M, K);
    cout << ans;
}