#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5050505;
const int L = 21;

int N, A[MAXN], Rin[1<<L], R[1<<L], Pre[L][L][MAXN/L/L];
vector<int> P[L][L];

int query(int idx, int s)
{
    for(; idx%(L*L) && idx+1 <= N; idx++) {
        if((~s&(1<<A[idx])) && (~s&(1<<A[idx+1]))) return idx-1;
    }
    if(idx >= N) return N;
    if((~s&(1<<A[idx])) && (~s&(1<<A[idx+1]))) return idx-1;
    idx /= L*L;
    int mn = N+1;
    for(int i = 0; i < L; i++) {
        if(s&(1<<i)) continue;
        for(int j = 0; j < L; j++) {
            if(s&(1<<j)) continue;
            mn = min(mn, Pre[i][j][idx]);
        }
    }
    return mn-1;
}

int step(int s, int num)
{
    for(int i = num; i >= 0; i--) {
        if(s&(1<<i)) {
            s^=(1<<i);
            break;
        }
    }
    return s | (1<<num);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> A[i]; A[i]--;
    }
    for(int i = 1; i+1 <= N; i++) {
        P[A[i]][A[i+1]].push_back(i);
    }
    for(int i = 0; i < L; i++) {
        for(int j = 0; j < L; j++) {
            P[i][j].push_back(N+1);
            sort(P[i][j].begin(), P[i][j].end());
            int p = 0;
            int q = 0;
            for(int k = 0; k <= N; k += L*L, q++) {
                while(P[i][j][p] < k) p++;
                Pre[i][j][q] = P[i][j][p];
            }
        }
    }
    memset(Rin, -1, sizeof(Rin));
    Rin[0] = 0;
    int ans = 1e9;
    for(int i = 0; i < (1<<L); i++) {
        if(Rin[i] == -1) continue;
        R[i] = query(Rin[i]+1, i);
        if(R[i]+1 <= N) Rin[step(i, A[R[i]+1])] = max(Rin[step(i, A[R[i]+1])], R[i]+1);
        if(R[i]+2 <= N) Rin[step(i, A[R[i]+2])] = max(Rin[step(i, A[R[i]+2])], R[i]+2);
        if(R[i] >= N-1) ans = min(ans, popcount((unsigned)i));
    }
    cout << ans << "\n";
}