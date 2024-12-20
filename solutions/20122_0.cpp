#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 10;

int N, M, a, b, c, jail[MAXN][MAXN], mncache[1<<MAXN][1<<MAXN], mxcache[1<<MAXN][1<<MAXN], mnchk[1<<MAXN][1<<MAXN], mxchk[1<<MAXN][1<<MAXN];

int compute(int org, int j)
{
    if(j == 0) return org;
    else if(j == 1) return org + a;
    else if(j == 2) return org + b;
    else if(j == 3) return org * c;
    assert(0);
}

int mndp(int ver, int hor);
int mxdp(int ver, int hor);

int mndp(int ver, int hor)
{
    int& ret = mncache[ver][hor];
    if(mnchk[ver][hor]) return ret;
    mnchk[ver][hor] = true;

    ret = 0;
    for(int i = 0; i < N; i++) {
        if(ver&(1<<i)) continue;
        int cand1 = mndp(ver|(1<<i), hor);
        int cand2 = mxdp(ver|(1<<i), hor);
        for(int j = M-1; j >= 0; j--) {
            if(hor&(1<<j)) continue;
            cand1 = compute(cand1, jail[i][j]);
            cand2 = compute(cand2, jail[i][j]);
        }
        ret = min(cand1, ret);
        ret = min(cand2, ret);
    }

    for(int j = 0; j < M; j++) {
        if(hor&(1<<j)) continue;
        int cand1 = mndp(ver, hor|(1<<j));
        int cand2 = mxdp(ver, hor|(1<<j));
        for(int i = N-1; i >= 0; i--) {
            if(ver&(1<<i)) continue;
            cand1 = compute(cand1, jail[i][j]);
            cand2 = compute(cand2, jail[i][j]);
        }
        ret = min(cand1, ret);
        ret = min(cand2, ret);
    }
    return ret;
}

int mxdp(int ver, int hor)
{
    int& ret = mxcache[ver][hor];
    if(mxchk[ver][hor]) return ret;
    mxchk[ver][hor] = true;

    ret = 0;
    for(int i = 0; i < N; i++) {
        if(ver&(1<<i)) continue;
        int cand1 = mndp(ver|(1<<i), hor);
        int cand2 = mxdp(ver|(1<<i), hor);
        for(int j = M-1; j >= 0; j--) {
            if(hor&(1<<j)) continue;
            cand1 = compute(cand1, jail[i][j]);
            cand2 = compute(cand2, jail[i][j]);
        }
        ret = max(cand1, ret);
        ret = max(cand2, ret);
    }

    for(int j = 0; j < M; j++) {
        if(hor&(1<<j)) continue;
        int cand1 = mndp(ver, hor|(1<<j));
        int cand2 = mxdp(ver, hor|(1<<j));
        for(int i = N-1; i >= 0; i--) {
            if(ver&(1<<i)) continue;
            cand1 = compute(cand1, jail[i][j]);
            cand2 = compute(cand2, jail[i][j]);
        }
        ret = max(cand1, ret);
        ret = max(cand2, ret);
    }
    return ret;
}

signed main()
{
    cin >> N >> M >> a >> b >> c;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cin >> jail[i][j];
        }
    }

    int mn = mndp(0, 0);
    int mx = mxdp(0, 0);
    cout << mn << " " << mx;
}