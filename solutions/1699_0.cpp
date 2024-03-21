#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
const int INF = 987654321;

int n, cache[MAXN];

int f(int x)
{
    if(x == 0) return 0;
    int& ret = cache[x];
    if(ret != -1) return ret;

    ret = INF;
    for(int i = 1; i * i <= x; i++) {
        ret = min(f(x - i * i) + 1, ret);
    }
    return ret;
}

int main()
{
    cin >> n;
    memset(cache, -1, sizeof(cache));
    int cnt = f(n);
    cout << cnt;
}