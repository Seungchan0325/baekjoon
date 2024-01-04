#include <bits/stdc++.h>

using namespace std;

int n, m, k, q, cache[301][301];
char board[301][301];

bool play(int r, int c) {
    if(r == n && c == m) return false;

    int& ret = cache[r][c];
    if(ret != -1) return ret;

    if(r < n)
        if(!play(r + 1, c) && board[r+1][c] == '.')
            return ret = true;
    
    if(c < m)
        if(!play(r, c + 1) && board[r][c+1] == '.')
            return ret = true;
    
    for(int i=1; i<=k; i++) {
        //if(board[r + i][c + i] == '#') break;
        if(r + i > n || c + i > m) break;

        if(!play(r + i, c + i) && board[r+i][c+i] == '.')
            return ret = true;
    }

    return ret = false;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin>>n>>m>>k;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            cin>>board[i][j];

    memset(cache, -1, sizeof(cache));
    cin>>q;
    while(q--) {
        int r, c; cin>>r>>c;

        if(play(r, c)) {
            cout<<"First\n";
        } else {
            cout<<"Second\n";
        }
    }
}