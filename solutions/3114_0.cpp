#include <bits/stdc++.h>

using namespace std;

const int MAXRC = 1505;

int R, C;
int dp[MAXRC][MAXRC];
int apples[MAXRC][MAXRC];
int bananas[MAXRC][MAXRC];

int main() {
    cin >> R >> C;
    for(int i = 1; i <= R; i++) {
        for(int j = 1; j <= C; j++) {
            char fruit;
            int count;
            cin >> fruit >> count;
            if(fruit == 'A') apples[i][j] = count;
            if(fruit == 'B') bananas[i][j] = count;
        }
    }

    for(int i = 1; i <= R; i++)
        for(int j = 1; j <= C; j++) {
            apples[i][j] += apples[i-1][j];
            bananas[i][j] += bananas[i][j-1];
        }
    
    for(int i = 1; i <= R; i++) {
        for(int j = 1; j <= C; j++) {
            int new_apples = apples[R][j] - apples[i][j];
            int new_bananas = bananas[i][C] - bananas[i][j];
            dp[i][j+1] = max(dp[i][j] + new_apples, dp[i][j+1]);
            dp[i+1][j] = max(dp[i][j] + new_bananas, dp[i+1][j]);
            dp[i+1][j+1] = max(dp[i][j] + new_apples + new_bananas, dp[i+1][j+1]);
        }
    }

    // for(int i = 1; i <= R; i++) {
    //     for(int j = 1; j <= C; j++) cout << dp[i][j] << " ";
    //     cout << "\n";
    // }

    cout << dp[R][C];
}