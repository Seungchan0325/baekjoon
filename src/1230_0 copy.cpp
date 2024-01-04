#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;

int cache[1005][1005];
string o, n;

int dp(int s1, int s2)
{
    if(s1 > o.size() || s2 > n.size()) return INF;
    if(s1 == o.size())
    {
        if(s2 == n.size()) return 0;
        return 1;
    }

    int& ret = cache[s1][s2];
    if(ret != -1) return ret;

    ret = INF;
    ret = min(dp(s1, s2 + 1), ret);
    int ns2 = s2;
    for(int ns1 = s1; ns1 < o.size(); ns1++)
    {
        if(o[ns1] != n[ns2]) break;
        int res = dp(ns1 + 1, ns2 + 1);
        if(s1 == 0 && 0 < s2) res++;
        ret = min(res + 1, ret);
        ns2++;
    }
    return ret;
}

int main()
{
    getline(cin, o);
    getline(cin, n);

    memset(cache, -1, sizeof(cache));
    int result = dp(0, 0);
    if(result >= INF) cout << "-1";
    else cout << result - 1;
}