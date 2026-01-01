#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3030;

int N, M, G[MAXN][MAXN], l[MAXN][MAXN], r[MAXN][MAXN], ll[MAXN][MAXN], rr[MAXN][MAXN], ld[MAXN+MAXN], rd[MAXN+MAXN], mx[MAXN][MAXN];

int main()
{
    cin >> N >> M;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            char c; cin >> c;
            G[i][j] = c - '0';
        }
    }

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            if(G[i][j]) {
                l[i][j] = 1;
                if(G[i-1][j-1]) l[i][j] = l[i-1][j-1] + 1;
            }
            if(G[i][j]) {
                r[i][j] = 1;
                if(G[i-1][j+1]) r[i][j] = r[i-1][j+1] + 1;
            }
        }
    }

    for(int i = N; i >= 1; i--) {
        for(int j = 1; j <= M; j++) {
            if(G[i][j]) {
                int v = l[i][j] + r[i][j] - 1;
                ll[i][j] = v;
                rr[i][j] = v;
                ll[i][j] = max({ll[i][j], ll[i+1][j+1]});
                rr[i][j] = max({rr[i][j], rr[i+1][j-1]});
            }
        }
    }

    int ans = 0;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            if(G[i][j]) {
                ans = max(ans, ll[i+1][j+1] + rr[i+1][j-1] - min(l[i][j], r[i][j]));
            }
            ans = max(ans, ll[i][j+1] + rr[i][j]);
        }
    }

    for(int i = N+M; i > M; i--) {
        ld[i] = ld[i+1];
        int x = i-M;
        int y = 1;
        while(x <= N && y <= M) {
            if(G[x][y]) ld[i] = max(ld[i], rr[x][y] - r[x][y] + 1);
            x++; y++;
        }
    }
    for(int i = M; i >= 2; i--) {
        ld[i] = ld[i+1];
        int x = 1;
        int y = M-i+2;
        while(x <= N && y <= M) {
            if(G[x][y]) ld[i] = max(ld[i], rr[x][y] - r[x][y] + 1);
            x++; y++;
        }
    }
    for(int i = N+M; i > M; i--) {
        rd[i] = rd[i+1];
        int x = i-M;
        int y = M;
        while(x <= N && y >= 1) {
            if(G[x][y]) rd[i] = max(rd[i], ll[x][y] - l[x][y] + 1);
            x++; y--;
        }
    }
    for(int i = M; i >= 2; i--) {
        rd[i] = rd[i+1];
        int x = 1;
        int y = i-1;
        while(x <= N && y >= 1) {
            if(G[x][y]) rd[i] = max(rd[i], ll[x][y] - l[x][y] + 1);
            x++; y--;
        }
    }
    for(int i = N; i >= 1; i--) {
        for(int j = 1; j <= M; j++) {
            mx[i][j] = max({mx[i+1][j-1], mx[i+1][j], mx[i+1][j+1], l[i][j] + r[i][j] - 1});
        }
    }

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            ans = max(ans, l[i][j] + r[i][j] - 1 + max({mx[i+1][j], ld[i-j+2+M], rd[i+j+1]}));
        }
    }
    cout << ans << "\n";
}