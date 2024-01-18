#include <bits/stdc++.h>

using namespace std;

int dp[102][102][102];

void make_dp() {
    int a, b, c;
    dp[20+50][20+50][20+50] = 1048576;
    for(a = -50; a <= 50; a++) { 
        for(b = -50; b <= 50; b++) {
            for(c = -50; c <= 50; c++) {
                if(a <= 0 || b <= 0 || c <= 0) {
                    dp[a+50][b+50][c+50] = 1;
                }
                else if(a > 20 || b > 20 || c > 20) {
                    dp[a+50][b+50][c+50] = dp[20+50][20+50][20+50];
                } else if(a < b && b < c) {
                    dp[a+50][b+50][c+50] = 
                        dp[a+50][b+50][c-1+50] +
                        dp[a+50][b-1+50][c-1+50] -
                        dp[a+50][b-1+50][c+50];
                } else {
                    dp[a+50][b+50][c+50] = 
                        dp[a-1+50][b+50][c+50] +
                        dp[a-1+50][b-1+50][c+50] +
                        dp[a-1+50][b+50][c-1+50] -
                        dp[a-1+50][b-1+50][c-1+50];
                }
            }
        }
    }
}

int main() {
    make_dp();
    int a, b, c;
    while(true) {
        scanf("%d %d %d", &a, &b, &c);
        if(a == -1 && b == -1 && c == -1) break;
        printf("w(%d, %d, %d) = %d\n", a, b, c, dp[a+50][b+50][c+50]);
    }
}