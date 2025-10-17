#ifdef LSC_ENV
#include "grader.cpp"
#endif

#include <bits/stdc++.h>
#include "evolution2.h"

using namespace std;

const int MAXN = 10101;

int N;
vector<int> G[MAXN];
vector<int> S[MAXN];

struct cmp {
    bool operator () (int i, int j) {
        return compare(i, j);
    }
};

int l2(int x) {
    int k=0;
    while ((1<<k)<x) {
        k++;
    }
    return k;
}

void dfs(int u, int p)
{
    for(auto v : G[u]) {
        if(v == p) continue;
        dfs(v, u);
        int A = S[u].size();
        int B = S[v].size();
        if(A == 0) {
            S[u] = S[v];
            continue;
        }
        if(A < B) swap(S[u], S[v]), swap(A, B);
        int C = 0;
        int x = A+B-1;
        int y = B*l2(A+1);
        int z = 1e9;
        for(int k = 1; k < A; k = 2*k + 1) {
            int val = (A+k-1)/k+B+B*l2(k+1)-2;
            if(val<z) {
                z = val;
                C = k;
            }
        }
        if(x <= y && x <= z) {
            vector<int> SS(A+B);
            merge(S[u].begin(), S[u].end(),
                  S[v].begin(), S[v].end(),
                  SS.begin(), cmp());
            S[u] = SS;
        } else if(y <= x && y <= z) {
            vector<int>::iterator it = S[u].begin();
            for(int i : S[v]) {
                it = lower_bound(it, S[u].end(), i, cmp());
                it = next(S[u].insert(it, i));
            }
        } else {
            int l = 0;
            int r = C;
            for(int i = 0; i < B;) {
                while(i < B && (r >= A || compare(S[v][i], S[u][r]))) {
                    int lo = l-1;
                    int hi = min(r, A);
                    while(lo+1 < hi) {
                        int mid = (lo+hi)/2;
                        if(compare(S[u][mid], S[v][i])) lo = mid;
                        else hi = mid;
                    }
                    S[u].insert(S[u].begin()+hi, S[v][i]);
                    l = hi+1;
                    r++; A++; i++;
                }
                l = r; r = l + C;
            }
        }
    }
    S[u].insert(S[u].begin(), u);
}

vector<int> recover(int _N, vector<int> U, vector<int> V) {
    N = _N;
    for(int i = 0; i < N; i++) {
        G[i].clear();
        S[i].clear();
    }
    for(int i = 0; i < U.size(); i++) G[U[i]].push_back(V[i]), G[V[i]].push_back(U[i]);
    dfs(0, -1);
    vector<int> A(N);
    for(int i = 0; i < N; i++) A[S[0][i]] = i;
    return A;
}
