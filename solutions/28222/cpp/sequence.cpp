#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include "sequence.h"

#ifndef BOJ
#include "grader.cpp"
#endif

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Node {
    int mn, mx;
};

const int MAXN = 5050505;
const int inf = 1e9;

Node merge(Node a, Node b)
{
    return {min(a.mn, b.mn), max(a.mx, b.mx)};
}

struct LazySegTree {
    int lazy[4*MAXN] = {};
    Node tree[4*MAXN] = {};
    void push(int s, int e, int idx)
    {
        if(lazy[idx]) {
            tree[idx].mn += lazy[idx];
            tree[idx].mx += lazy[idx];
            if(s != e) {
                lazy[2*idx] += lazy[idx];
                lazy[2*idx+1] += lazy[idx];
            }
            lazy[idx] = 0;
        }
    }
    
    void update(int l, int r, int v, int s=0, int e=MAXN-1, int idx=1)
    {
        push(s, e, idx);
        if(e < l || r < s) return;
        if(l <= s && e <= r) {
            lazy[idx] += v;
            push(s, e, idx);
            return;
        }
        int m = (s + e) / 2;
        update(l, r, v, s, m, 2*idx);
        update(l, r, v, m+1, e, 2*idx+1);
        tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
    }
    
    Node query(int l, int r, int s=0, int e=MAXN-1, int idx=1)
    {
        push(s, e, idx);
        if(e < l || r < s) return {inf, -inf};
        if(l <= s && e <= r) return tree[idx];
        int m = (s + e) / 2;
        return merge(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
    }
};

vector<int> nums[MAXN];
LazySegTree x, y;

int sequence(int N, std::vector<int> A) {
    for(int i = 0; i < N; i++) {
        nums[A[i]].push_back(i+1);
    }

    int ans = 0;
    for(int i = 1; i <= N; i++) x.update(i, i, i), y.update(i, i, i);
    for(int i = 1; i <= N; i++) {
        int r = 0;
        for(auto j : nums[i]) y.update(j, N, -2);
        for(int l = 0; l < nums[i].size(); l++) {
            while(r < nums[i].size()) {
                ll v1 = x.query(nums[i][r], N).mx - x.query(0, nums[i][l]).mn;
                ll v2 = y.query(nums[i][r], N).mn - y.query(0, nums[i][l]).mx;
                if(v1 * v2 <= 0) ans = max(ans, r-l+1), r++;
                else break;
            }
        }
        for(auto j : nums[i]) x.update(j, N, -2);
    }
    return ans;
}
