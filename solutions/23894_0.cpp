#include <bits/stdc++.h>

using namespace std;

const int MAXN = 202020;
const int LOGN = 30;

int N, f[MAXN], Q, sparse[LOGN][MAXN];

int fm(int x, int m)
{
    for(int i = 0; i < LOGN; i++) {
        if(m&(1<<i)) x = sparse[i][x];
    }
    return x;
}

int until_one(int x)
{
    int step = 0;
    for(int i = LOGN-1; i >= 0; i--) {
        if(sparse[i][x]) {
            step += 1<<i;
            x = sparse[i][x];
        }
    }
    return step;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i <= N; i++) cin >> f[i];

    for(int i = 2; i <= N; i++) sparse[0][i] = f[i];
    for(int i = 1; i < LOGN; i++) {
        for(int j = 1; j <= N; j++) {
            sparse[i][j] = sparse[i-1][sparse[i-1][j]];
        }
    }
    
    cin >> Q;
    while(Q--) {
        int op; cin >> op;
        if(op == 1) {
            int x; cin >> x;
            f[1] = x;
        } else {
            int m, x; cin >> m >> x;
            x = f[x]; m--;
            auto step = until_one(x);
            if(m <= step) {
                cout << fm(x, m) << "\n";
            } else {
                m -= step;
                if(f[1] == 1) {
                    cout << "1\n";
                    continue;
                }
                x = f[1]; m--;
                auto step = until_one(x);
                if(m <= step) {
                    cout << fm(x, m) << "\n";
                } else {
                    int cycle_sz = step + 1;
                    cout << fm(x, m % cycle_sz) << "\n";
                }
            }
        }
    }
}