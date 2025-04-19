#include "grader.cpp"

#include "mosaic.h"

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

vector<int> propagate(vector<int> p, int x)
{
    vector<int> v(p.size());
    v[1] = !x && !p[1];
    for(int i = 2; i < p.size(); i++)
        v[i] = !v[i-1] && !p[i];
    return v;
}

vector<ll> mosaic(vector<int> c0, vector<int> r0, vector<int> T, vector<int> B, vector<int> L, vector<int> R) {
    int Q = (int)T.size();
    vector<ll> C(Q, 0);

    auto r1 = propagate(r0, c0[1]);
    auto r2 = propagate(r1, c0[2]);
    auto c1 = propagate(c0, r0[1]);
    auto c2 = propagate(c1, r0[2]);

    r0[0] = 0;
    r1[0] = r1[1] = 0;
    r2[0] = r2[1] = r2[2] = 0;
    c1[0] = 0;
    c2[0] = c2[1] = 0;

    vector<ll> sr(r2.size()), sc(c2.size());

    for(int i = 1; i < r2.size(); i++) {
        sr[i] += sr[i-1] + (r2[i] ? i : 0);
        r0[i] += r0[i-1];
        r1[i] += r1[i-1];
        r2[i] += r2[i-1];
    }
    for(int i = 1; i < c2.size(); i++) {
        sc[i] += sc[i-1] + (c2[i] ? i : 0);
        c0[i] += c0[i-1];
        c1[i] += c1[i-1];
        c2[i] += c2[i-1];
    }

    auto query = [&](int y, int x) {
        ll ans = 0;
        if(y >= 0 && x >= 0) ans += c0[x];
        if(y >= 1 && x >= 0) ans += c1[x];
        if(x >= 0 && y >= 0) ans += r0[y];
        if(x >= 1 && y >= 0) ans += r1[y];
        if(x >= 2 && y >= 2) {
            if(x < y) {
                ans += (ll)(x + 1) * c2[x] - sc[x];
                ans += (ll)(x - 1) * r2[y-x+1];
                ans += (ll)(y + 1) * (r2[y] - r2[y-x+1]) - (sr[y] - sr[y-x+1]);
            } else {
                ans += (ll)(y + 1) * r2[y] - sr[y];
                ans += (ll)(y - 1) * c2[x-y+1];
                ans += (ll)(x + 1) * (c2[x] - c2[x-y+1]) - (sc[x] - sc[x-y+1]);
            }
        }
        return ans;
    };

    for(int i = 0; i < Q; i++) {
        C[i] += query(B[i], R[i]);
        C[i] -= query(T[i]-1, R[i]);
        C[i] -= query(B[i], L[i]-1);
        C[i] += query(T[i]-1, L[i]-1);
    }

    return C;
}
