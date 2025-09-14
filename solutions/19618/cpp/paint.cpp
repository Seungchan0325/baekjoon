#ifdef LSC_ENV
#include "grader.cpp"
#endif

#include "paint.h"

#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;
const int MAXN = 101010;
const int MAXM = 50505;
const int MAXK = 101010;

int val[2][650];
vector<int> r[MAXK];

int minimumInstructions(int N, int M, int K, vector<int> C, vector<int> A, vector<vector<int>> B) {
    for(int i = 0; i < M; i++) {
        for(int j = 0; j < A[i]; j++) {
            r[B[i][j]].push_back(i);
        }
    }
    C.insert(C.begin(), MAXK-1);
    deque<pair<int, int>> dq;
    dq.push_back({0, 0});
    int v;
    for(int i = 1; i <= N; i++) {
        v = INF;
        int q = 0;
        bool pos = false;
        for(int k = 0; k < r[C[i]].size(); k++) {
            int j = r[C[i]][k];
            int p = (j+M-1)%M;
            while(q < r[C[i-1]].size() && r[C[i-1]][q] < p) q++;
            if(q == r[C[i-1]].size() || r[C[i-1]][q] != p) val[i%2][k] = 1;
            else val[i%2][k] = min(val[(i+1)%2][q] + 1, M);
            if(val[i%2][k] == M) pos = true;
            if(k == 0) q = 0;
        }
        if(pos) {
            while(i - dq[0].second > M) dq.pop_front();
            if(dq.size()) v = dq[0].first + 1;
        }
        while(dq.size() && dq.back().first > v) dq.pop_back();
        dq.push_back({v, i});
    }
    if(v >= INF) return -1;
    return v;
}
