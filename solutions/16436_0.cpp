#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5050;

int W, H, K, R[MAXN][MAXN], D[MAXN][MAXN], A[MAXN][MAXN];

int main()
{
    cin >> W >> H >> K;
    for(int i = 1; i <= K; i++) {
        int op;
        cin >> op;
        if(op == 1) {
            int px, py, qx, qy;
            cin >> px >> py >> qx >> qy;
            R[py][px] ^= 1;
            R[qy+1][px] ^= 1;
            R[py][qx+1] ^= 1;
            R[qy+1][qx+1] ^= 1;
        } else {
            int x, y, r;
            cin >> x >> y >> r;
            int px = x - y - r + H;
            int py = x + y - r;
            int qx = x - y + r + H;
            int qy = x + y + r;
            D[py][px] ^= 1;
            D[qy+1][px] ^= 1;
            D[py][qx+1] ^= 1;
            D[qy+1][qx+1] ^= 1;
        }
    }

    for(int i = 0; i < W; i++) {
        for(int j = 1; j < H; j++) {
            R[j][i] ^= R[j-1][i];
        }
    }
    for(int j = 0; j < H; j++) {
        for(int i = 1; i < W; i++) {
            R[j][i] ^= R[j][i-1];
        }
    }

    for(int i = 0; i < W + H; i++) {
        for(int j = 1; j < W + H; j++) {
            D[j][i] ^= D[j-1][i];
        }
    }
    for(int j = 0; j < W + H; j++) {
        for(int i = 1; i < W + H; i++) {
            D[j][i] ^= D[j][i-1];
            
        }
    }

    for(int i = 0; i < W; i++) {
        for(int j = 0; j < H; j++) {
            int x = i - j + H;
            int y = i + j;
            A[j][i] = R[j][i] ^ D[y][x];
        }
    }

    for(int j = 0; j < H; j++) {
        for(int i = 0; i < W; i++) {
            if(A[j][i]) cout << "#";
            else cout << ".";
        }
        cout << "\n";
    }
}