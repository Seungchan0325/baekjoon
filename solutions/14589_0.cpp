#include <bits/stdc++.h>

using namespace std;

const int MAXN = 151010;
const int LOGN = 20;

int N, Q, S[MAXN], E[MAXN], sparse[MAXN][LOGN+1];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> S[i] >> E[i];
    }

    vector<int> v1(N), v2(N);
    iota(v1.begin(), v1.end(), 1);
    iota(v2.begin(), v2.end(), 1);
    sort(v1.begin(), v1.end(), [](int i, int j){return E[i] < E[j];});
    sort(v2.begin(), v2.end(), [](int i, int j){return S[i] < S[j];});
    int idx = 0;
    int mx = -1e9;
    int mxi = -1;
    for(auto i : v1) {
        while(idx < N && S[v2[idx]] <= E[i]) {
            if(mx < E[v2[idx]]) {
                mx = E[v2[idx]];
                mxi = v2[idx];
            }
            idx++;
        }
        if(mx > E[i]) {
            sparse[i][0] = mxi;
        }
    }

    for(int j = 1; j <= LOGN; j++)
        for(int i = 1; i <= N; i++)
            sparse[i][j] = sparse[sparse[i][j-1]][j-1];
    
    cin >> Q;
    while(Q--) {
        int s, e;
        cin >> s >> e;

        if(S[s] > E[e]) swap(s, e);
        if(S[e] <= E[s]) {
            cout << "1\n";
            continue;
        }

        int ans = 0;
        for(int j = LOGN; j >= 0; j--) {
            if(sparse[s][j] != 0 && E[sparse[s][j]] < E[e]) {
                s = sparse[s][j];
                ans += 1<<j;
            }
        }

        if(E[s] < S[e]) {
            if(sparse[s][0] == 0) {
                cout << "-1\n";
                continue;
            }
            s = sparse[s][0], ans++;
        }
        if(e != s) ans++;

        if(S[e] <= E[s]) cout << ans << "\n";
        else cout << "-1\n";
    }
}