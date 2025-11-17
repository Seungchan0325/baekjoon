#include <bits/stdc++.h>

using namespace std;

int dp[3000][3000][2];

bool query(int x)
{
    cout << "? " << x << endl;
    int ret; cin >> ret;
    return ret;
}

void answer(int x)
{
    cout << "! " << x << endl;
}

int mysearch(int l, int r, int lied)
{
    if(l == r) return 0;
    int& dep = dp[l][r][lied];
    if(dep != -1) return dep;
    dep = 1e9;
    for(int x = l+1; x <= r; x++) {
        if(lied) dep = min(max(mysearch(l, x-1, lied)+1, mysearch(x, r, lied)+1), dep);
        else dep = min(max({mysearch(l, x-1, false)+1, mysearch(l, x-1, true)+2, mysearch(x, r, false)+2}), dep);
    }
    return dep;
}

int solve(int l, int r, int lied)
{
    if(l == r) return l;
    int opt = -1;
    for(int x = l+1; x <= r; x++) {
        if(lied) {
            if(max(mysearch(l, x-1, lied)+1, mysearch(x, r, lied)+1) == mysearch(l, r, lied))
                opt = x;
        } else {
            if(max({mysearch(l, x-1, false)+1, mysearch(l, x-1, true)+2, mysearch(x, r, false)+2}) == mysearch(l, r, lied))
                opt = x;
        }
    }

    if(lied) {
        if(!query(opt)) return solve(l, opt-1, lied);
        else return solve(opt, r, lied);
    }

    if(!query(opt)) return solve(l, opt-1, false);
    else if(!query(opt)) return solve(l, opt-1, true);
    else return solve(opt, r, false);
}

int main()
{
    memset(dp, -1, sizeof(dp));

    int t; cin >> t;
    while(t--) {
        int x = solve(2100, 2399, false);
        answer(x);
    }
}