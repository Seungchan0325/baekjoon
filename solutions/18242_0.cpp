#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;

int N, M;
char board[MAXN][MAXN];

int main()
{
    cin >> N >> M;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cin >> board[i][j];
        }
    }

    for(int i = 0; i < N; i++) {
        for(int j = 1; j < M - 1; j++) {
            if(board[i][j-1] == '#' && board[i][j] == '.' && board[i][j+1] == '#') {
                bool flag = false;
                for(int k = 0; k < i; k++) {
                    if(board[k][j] == '#') {
                        flag = true;
                        break;
                    }
                }

                if(flag) cout << "DOWN";
                else cout << "UP";
                return 0;
            }
        }
    }

    for(int i = 1; i < N - 1; i++) {
        for(int j = 0; j < M; j++) {
            if(board[i-1][j] == '#' && board[i][j] == '.' && board[i+1][j] == '#') {
                bool flag = false;
                for(int k = 0; k < j; k++) {
                    if(board[i][k] == '#') {
                        flag = true;
                        break;
                    }
                }

                if(flag) cout << "RIGHT";
                else cout << "LEFT";
                return 0;
            }
        }
    }
    assert(0);
}