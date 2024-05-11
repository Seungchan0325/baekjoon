#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;

int N, M[MAXN][MAXN];

int main()
{
    cin >> N;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> M[i][j];
        }
    }

    for(int i = 0; i < N; i++) {
        int ai = 0;
        for(int j = 0; j < N; j++) {
            ai |= M[i][j];
        }
        cout << ai << " ";
    }
}