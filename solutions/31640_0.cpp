#include <bits/stdc++.h>

using namespace std;

const int MAXN = 512;

int N, M, K, cache[MAXN][MAXN][8][8][8];
char S[MAXN], T[MAXN];

int inc(int c, int ij)
{
    if(c < 3) return c + (ij == 0 || ij == 2);
    if(c < 6) return c + (ij == 1 || ij == 2);
    return c;
}

char get(int i, int j, int p)
{
    if(p < 3) return S[i-p-1];
    if(p < 6) return T[j-p+2];
    return '#';
}

bool ok(char c, char c1, char c2, char c3)
{
    if(K == 0) return true;
    if(c == c3) return false;
    if(K == 1) return true;
    if(c == c2) return false;
    if(K == 2) return true;
    if(c == c1) return false;
    return true;
}

int dp(int i, int j, int i1, int i2, int i3)
{
    if(i == N && j == M) return 0;
    int& ret = cache[i][j][i1][i2][i3];
    if(ret != -1) return ret;

    ret = 1e9;
    char c1 = get(i, j, i1);
    char c2 = get(i, j, i2);
    char c3 = get(i, j, i3);

    if(c1 != '#' || c2 != '#' || c3 != '#') ret = min(ret, dp(i, j, inc(i2, 3), inc(i3, 3), 6) + 1);
    if(i < N && ok(S[i], c1, c2, c3)) ret = min(ret, dp(i+1, j, inc(i2, 0), inc(i3, 0), 0) + 1);
    if(j < M && ok(T[j], c1, c2, c3)) ret = min(ret, dp(i, j+1, inc(i2, 1), inc(i3, 1), 3) + 1);
    if(i < N && j < M && S[i] == T[j] && ok(S[i], c1, c2, c3)) ret = min(ret, dp(i+1, j+1, inc(i2, 2), inc(i3, 2), 0) + 1);
    return ret;
}

int main()
{
    cin >> N >> M >> K;
    cin >> S;
    cin >> T;
    memset(cache, -1, sizeof(cache));
    int ans = dp(0, 0, 6, 6, 6);
    cout << ans << "\n";
}