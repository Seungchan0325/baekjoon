#include "nile.h"

// #include "grader.cpp"

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll inf = 1e18;

struct Group {
    int sz = 1;
    ll ans = 0;
    ll sum = 0;
    ll evenMin = inf;
    ll oddMin = inf;
    ll evenMinAll = inf;
    ll oddMinAll = inf;
};

struct DSU {
    vector<int> root;
    DSU(int n) : root(n+1) {
        iota(root.begin(), root.end(), 0);
    }
    int find(int x) {
        if(root[x] == x) return x;
        return root[x] = find(root[x]);
    }
    void merge(int x, int y) {
        x = find(x);
        y = find(y);
        root[y] = x;
    }
};

std::vector<ll> calculate_costs(std::vector<int> W, std::vector<int> A, std::vector<int> B, std::vector<int> E) {
    ll N = W.size();
    ll Q = (ll)E.size();
    std::vector<ll> R(Q, 0);

    vector<tuple<int, int, int>> jobs; jobs.reserve(N);
    for(int i = 0; i < N; i++) {
        jobs.emplace_back(W[i], A[i], B[i]);
    }
    sort(jobs.begin(), jobs.end());
    for(int i = 0; i < N; i++) {
        tie(W[i], A[i], B[i]) = jobs[i];
    }

    vector<pair<ll, ll>> m; m.reserve(N);
    for(ll i = 1; i < N; i++) {
        m.emplace_back((ll)W[i] - (ll)W[i-1], i);
    }
    sort(m.begin(), m.end());

    vector<pair<ll, ll>> s; s.reserve(N);
    for(ll i = 1; i+1 < N; i++) {
        s.emplace_back((ll)W[i+1] - (ll)W[i-1], i);
    }
    sort(s.begin(), s.end());
    
    vector<pair<ll, ll>> qrys; qrys.reserve(Q);
    for(ll i = 0; i < Q; i++) {
        qrys.emplace_back(E[i], i);
    }
    sort(qrys.begin(), qrys.end());

    ll ans = 0;
    vector<Group> groups; groups.reserve(N);
    for(ll i = 0; i < N; i++) {
        Group g;
        g.ans = A[i];
        g.sum = B[i];
        g.oddMinAll = (ll)A[i] - (ll)B[i];
        groups.push_back(g);

        ans += g.ans;
    }

    auto update = [&](Group& g)
    {
        ans -= g.ans;
        if(g.sz&1) {
            g.ans = g.sum + min(g.evenMin, g.oddMinAll);
        } else {
            g.ans = g.sum;
        }
        ans += g.ans;
    };

    ll mi = 0;
    ll si = 0;
    DSU dsu(N);
    for(ll i = 0; i < Q; i++) {
        while(mi < m.size() && m[mi].first <= qrys[i].first) {
            ll j = m[mi].second;
            ll x = dsu.find(j-1);
            ll y = dsu.find(j);
            auto& gx = groups[x];
            auto& gy = groups[y];
            if(gx.sz&1) {
                swap(gy.evenMin, gy.oddMin);
                swap(gy.evenMinAll, gy.oddMinAll);
            }
            
            gx.sz += gy.sz;
            gx.sum += gy.sum;
            gx.evenMin = min(gx.evenMin, gy.evenMin);
            gx.evenMinAll = min(gx.evenMinAll, gy.evenMinAll);
            gx.oddMin = min(gx.oddMin, gy.oddMin);
            gx.oddMinAll = min(gx.oddMinAll, gy.oddMinAll);

            ans -= gy.ans;
            update(gx);
            dsu.merge(j-1, j);
            mi++;
        }

        while(si < s.size() && s[si].first <= qrys[i].first) {
            ll j = s[si].second;
            ll start = dsu.find(j);
            auto& gs = groups[start];
            if((j-start+1)&1) {
                gs.oddMin = min<ll>(gs.oddMin, (ll)A[j] - (ll)B[j]);
            } else {
                gs.evenMin = min<ll>(gs.evenMin, (ll)A[j] - (ll)B[j]);
            }

            update(gs);
            si++;
        }

        R[qrys[i].second] = ans;
    }
    
    return R;
}
