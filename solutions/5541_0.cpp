#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5050;

int N, M, A[MAXN][MAXN];

int main()
{
    cin >> N >> M;
    for(int i = 0; i < M; i++) {
        int a, b, x;
        cin >> a >> b >> x;
        A[a][b]++;
        A[a][b+1]--;
        A[a+x+1][b]--;
        A[a+x+2][b+1]++;
        A[a+x+1][b+x+2]++;
        A[a+x+2][b+x+2]--;
    }

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            A[i][j] += A[i][j-1];
        }
    }
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            A[j][i] += A[j-1][i];
        }
    }
    for(int i = 1; i <= N; i++) {
        int a = i;
        int b = 1;
        while(a <= N && b <= N) {
            A[a+1][b+1] += A[a][b];
            a++; b++;
        }
    }

    int ans = 0;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= i; j++) {
            if(A[i][j]) ans++;
        }
    }
    cout << ans;
}