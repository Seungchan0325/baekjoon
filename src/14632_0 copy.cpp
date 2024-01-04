#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;
const int MAXK = 505;
const int MAXW = 505;

char board[MAXN][MAXN], stamp[MAXK][MAXW][MAXW];
int n, m, k, q, w[MAXK], h[MAXK];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(board, '.', sizeof(board));
    cin >> n >> m;
    cin >> k;
    for(int i = 1; i <= k; i++) {
        cin >> h[i] >> w[i];
        for(int j = 0; j < h[i]; j++)
            for(int k = 0; k < w[i]; k++)
                cin >> stamp[i][j][k]; 
    }
    cin >> q;
    while(q--) {
        int t, y, x; cin >> t >> y >> x;
        for(int i = 0; i < h[t]; i++)
            for(int j = 0; j < w[t]; j++)
                board[y+i][x+j] = stamp[t][i][j];
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            cout << board[i][j];
        cout << "\n";
    }
}