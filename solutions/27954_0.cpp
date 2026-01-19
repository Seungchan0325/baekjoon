#include <bits/stdc++.h>

using namespace std;

const int MAXN = 505050;

int N, M, Q;
char A[MAXN], B[MAXN], C[MAXN];

int idx(int i, int j)
{
    return i*M+j;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M >> Q;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cin >> A[idx(i, j)];
            B[idx(N-i-1, M-j-1)] = A[idx(i, j)];
        }
    }

    int ax = 0;
    int ay = 0;
    int zx = N-1;
    int zy = M-1;
    int c = 0;
    while(Q--) {
        int t;
        cin >> t;
        if(t == 1) {
            int x, y; cin >> x >> y; x--; y--;
            if(ax <= x) ax = x - ax;
            else ax = (N - x) - (ax - x) + x;
            if(ay <= y) ay = y - ay;
            else ay = (M - y) - (ay - y) + y;

            
            if(zx <= x) zx = x - zx;
            else zx = (N - x) - (zx - x) + x;
            if(zy <= y) zy = y - zy;
            else zy = (M - y) - (zy - y) + y;
            c ^= 1;
        } else {
            if(c == 0) {
                for(int i = 0; i < N; i++) {
                    for(int j = 0; j < M; j++) {
                        C[idx((i+ax)%N, (j+ay)%M)] = A[idx(i, j)];
                    }
                }
            } else {
                for(int i = 0; i < N; i++) {
                    for(int j = 0; j < M; j++) {
                        C[idx((i+zx)%N, (j+zy)%M)] = B[idx(i, j)];
                    }
                }
            }

            for(int i = 0; i < N; i++) {
                for(int j = 0; j < M; j++) {
                    cout << C[(idx(i, j))];
                }
                cout << "\n";
            }
        }
    }
}