#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 303030;
const ll inf = 1e18;

ll N, Q, X[MAXN], P[MAXN], sparse[25][MAXN], nxt[25][MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 0; i < N; i++) cin >> X[i] >> P[i];
    for(int i = 0; i+1 < N; i++) {
        ll s = X[i];
        ll t = 0;
        int k = 0;
        while(true) {
            t++;
            s = X[i]+P[i]*(1LL<<k);
            k++;
            if(s < X[i+1]) {
                t += s-X[i];
                s = X[i];
            } else {
                break;
            }
        }
        sparse[0][i] = t;
        nxt[0][i] = s;
    }
    for(int i = 1; i < 25; i++) {
        for(int j = 0; j+1 < N; j++) {
            int k = upper_bound(X, X+N, nxt[i-1][j]) - X - 1;
            if(k == N-1) sparse[i][j] = inf;
            else {
                sparse[i][j] = min(sparse[i-1][j] + sparse[i-1][k] + nxt[i-1][j] - X[k], inf);
                nxt[i][j] = nxt[i-1][k];
            }
        }
    }
    cin >> Q;
    while(Q--) {
        ll s, t;
        cin >> s >> t;

        for(int i = 24; i >= 0; i--) {
            int j = upper_bound(X, X+N, s) - X - 1;
            if(j < 0) {
                s -= t;
                t = 0;
                break;
            }
            if(s-X[j] >= t) {
                s -= t;
                t -= t;
                break;
            } else {
                t -= s-X[j];
                s = X[j];
            }
            if(j == N-1) break;
            if(sparse[i][j] <= t) {
                s = nxt[i][j];
                t -= sparse[i][j];
            }
        }
        int i = upper_bound(X, X+N, s) - X - 1;
        if(i < 0) {
            s -= t;
            t = 0;
        } else if(s-X[i] >= t) {
            s -= t;
            t -= t;
        } else {
            t -= s-X[i];
            s = X[i];
        }
        int k = 0;
        while(t > 0) {
            t--;
            s = X[i]+P[i]*(1LL<<k);
            k++;
            if(i+1 == N || s < X[i+1]) {
                if(t < s-X[i]) {
                    s = s-t;
                    t = 0;
                    break;
                } else {
                    t -= s-X[i];
                    s = X[i];
                }
            } else {
                break;
            }
        }

        cout << s << "\n";
    }
}