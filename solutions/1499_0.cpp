#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;

int n, cache[55][55][55][55][2];
string src, dst;

int dp(int i, int j, int ii, int jj, int d)
{
    if(jj < ii) return 0;

    int& ret = cache[i][j][ii][jj][d];
    if(ret != -1) return ret;

    ret = INF;
    if(d == 0) {
        if(src[i] == dst[ii]) ret = min(dp(i + 1, j, ii + 1, jj, 0), ret);
        if(src[j] == dst[jj]) ret = min(dp(i, j - 1, ii, jj - 1, 0), ret);
        if(src[i] == dst[ii] && src[j] == dst[jj]) ret = min(dp(i + 1, j - 1, ii + 1, jj - 1, 0), ret);

        if(src[j] == dst[ii]) ret = min(dp(i, j - 1, ii + 1, jj, 1) + 1, ret);
        if(src[i] == dst[jj]) ret = min(dp(i + 1, j, ii, jj - 1, 1) + 1, ret);
        if(src[j] == dst[ii] && src[i] == dst[jj]) ret = min(dp(i + 1, j - 1, ii + 1, jj - 1, 1) + 1, ret);
    } else {
        if(src[j] == dst[ii]) ret = min(dp(i, j - 1, ii + 1, jj, 1), ret);
        if(src[i] == dst[jj]) ret = min(dp(i + 1, j, ii, jj - 1, 1), ret);
        if(src[j] == dst[ii] && src[i] == dst[jj]) ret = min(dp(i + 1, j - 1, ii + 1, jj - 1, 1), ret);
        
        if(src[i] == dst[ii]) ret = min(dp(i + 1, j, ii + 1, jj, 0) + 1, ret);
        if(src[j] == dst[jj]) ret = min(dp(i, j - 1, ii, jj - 1, 0) + 1, ret);
        if(src[i] == dst[ii] && src[j] == dst[jj]) ret = min(dp(i + 1, j - 1, ii + 1, jj - 1, 0) + 1, ret);
    }

    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> src;
    cin >> dst;

    n = src.size();

    memset(cache, -1, sizeof(cache));
    int result = min(dp(0, n - 1, 0, n - 1, 0), dp(0, n - 1, 0, n - 1, 1) + 1);
    if(result >= INF) result = -1;
    cout << result;
}