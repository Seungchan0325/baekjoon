#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXQ = 150005;
const int LOGQ = 18;

int Q, sparse[MAXQ][LOGQ+1];
ll S[MAXQ];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> Q;

    int M = 0;
    int lst = 0;
    while(Q--) {
        string op;
        cin >> op;
        if(op == "query") {
            ll x, L;
            cin >> x >> L;

            ll dst = S[x] - L;
            for(int i = LOGQ; i >= 0; i--) {
                if(S[sparse[x][i]] > dst) {
                    x = sparse[x][i];
                }
            }
            if(S[sparse[x][0]] >= dst) x = sparse[x][0];
            cout << x << "\n";
            lst = x;
        } else {
            ll k, L;
            cin >> k >> L;
            M++;
            ll x = (k + lst) % M;

            S[M] = S[x] + L;
            sparse[M][0] = x;
            for(int i = 1; i <= LOGQ; i++) {
                sparse[M][i] = sparse[sparse[M][i-1]][i-1];
            }
        }
    }
}