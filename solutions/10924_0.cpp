#include <bits/stdc++.h>

using namespace std;

const int MAXN = 202020;
const int MAXM = 3*MAXN;

int N, S[MAXN], R[MAXN], M, X[MAXM], Y[MAXM];

bool chk(int K)
{
    vector<int> P(N);
    iota(P.begin(), P.end(), 0);
    for(int i = 0; i < K; i++) swap(P[X[i]], P[Y[i]]);
    int cnt = 0;
    vector<bool> vst(N);
    for(int i = 0; i < N; i++) {
        if(vst[i]) continue;
        int j = i;
        while(!vst[j]) {
            vst[j] = true;
            j = P[S[j]];
        }
        cnt++;
    }
    return N-cnt <= K;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for(int i = 0; i < N; i++) cin >> S[i], R[S[i]] = i;
    cin >> M;
    for(int i = 0; i < M; i++) cin >> X[i] >> Y[i];
    int lo = -1;
    int hi = M;
    while(lo+1 < hi) {
        int mid = (lo+hi)/2;
        if(chk(mid)) hi = mid;
        else lo = mid;
    }
    cout << hi << "\n";
    vector<int> P(N);
    iota(P.begin(), P.end(), 0);
    for(int i = 0; i < hi; i++) swap(P[X[i]], P[Y[i]]);
    vector<int> Q(N);
    for(int i = 0; i < N; i++) Q[P[i]] = i;
    int k = 0;
    for(int i = 0; i < hi; i++) {
        swap(P[Q[X[i]]], P[Q[Y[i]]]);
        swap(Q[X[i]], Q[Y[i]]);
        swap(R[S[X[i]]], R[S[Y[i]]]);
        swap(S[X[i]], S[Y[i]]);
        while(k < N && Q[R[k]] == k) k++;
        if(k == N) {
            cout << "0 0\n";
        } else {
            int p = P[k];
            int q = R[k];
            swap(R[S[p]], R[S[q]]);
            swap(S[p], S[q]);
            cout << p << " " << q << "\n";
        }
    }
}