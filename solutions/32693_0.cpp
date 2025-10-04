#include <bits/stdc++.h>

using namespace std;

int N, M;
bool issym[505][505][505];
char A[505][505];

int main()
{
    cin >> N >> M;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            cin >> A[i][j];
    for(int i = 0; i < N; i++) {
        for(int j = 0; j+1 < M; j++) {
            int a = j;
            int b = j+1;
            while(a >= 0 && b < M && A[i][a] == A[i][b]) {
                issym[i][a][b] = true;
                a--;
                b++;
            }
        }
    }

    long long ans = 0;
    for(int i = 0; i < M; i++) {
        for(int j = i+1; j < M; j+=2) {
            int p = 0;
            for(int k = 0; k < N; k++) {
                p = max(p, k);
                while(p < N && issym[p][i][j]) p++;
                ans += p-k;
            }
        }
    }
    cout << ans;
}