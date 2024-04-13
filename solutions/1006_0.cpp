#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int MAXN = 10005;

int N, W, arr[2][MAXN];
int dp[MAXN][4][4];

int main()
{
    int T;
    cin >> T;
    while(T--) {
        cin >> N >> W;
        for(int i = 0; i < N; i++) {
            cin >> arr[0][i];
        }
        for(int i = 0; i < N; i++) {
            cin >> arr[1][i];
        }

        if(N == 1) {
            if(arr[0][0] + arr[1][0] <= W) cout << 1 << '\n';
            else cout << 2 << "\n";
            continue;
        }

        memset(dp, 0x7F, sizeof(dp));

        dp[0][0b00][0b00] = 0;
        dp[0][0b11][0b00] = 2;
        dp[0][0b01][0b00] = 1;
        dp[0][0b10][0b00] = 1;
        if(arr[0][0] + arr[1][0] <= W) dp[0][0b11][0b00] = 1;
        if(arr[0][0] + arr[0][N-1] <= W && arr[1][0] + arr[1][N-1] <= W) dp[0][0b11][0b11] = 2;
        if(arr[0][0] + arr[0][N-1] <= W) { dp[0][0b11][0b01] = 2; dp[0][0b01][0b01] = 1; }
        if(arr[1][0] + arr[1][N-1] <= W) { dp[0][0b11][0b10] = 2; dp[0][0b10][0b10] = 1; }

        for(int i = 1; i < N - 1; i++) {
            for(int j = 0; j < 4; j++) {
                dp[i][0b00][j] = dp[i-1][0b11][j];
                dp[i][0b11][j] = dp[i-1][0b11][j] + 2;
                if(arr[0][i] + arr[1][i] <= W) dp[i][0b11][j] = dp[i-1][0b11][j] + 1;
                if(arr[0][i] + arr[0][i-1] <= W && arr[1][i] + arr[1][i-1] <= W) {
                    dp[i][0b11][j] = min(dp[i][0b11][j], dp[i-1][0b00][j] + 2);
                }

                dp[i][0b01][j] = dp[i-1][0b11][j] + 1;
                if(arr[0][i] + arr[0][i-1] <= W) {
                    dp[i][0b01][j] = min(dp[i][0b01][j], dp[i-1][0b10][j] + 1);
                    dp[i][0b11][j] = min(dp[i][0b11][j], dp[i-1][0b10][j] + 2);
                }

                dp[i][0b10][j] = dp[i-1][0b11][j] + 1;
                if(arr[1][i] + arr[1][i-1] <= W) {
                    dp[i][0b10][j] = min(dp[i][0b10][j], dp[i-1][0b01][j] + 1);
                    dp[i][0b11][j] = min(dp[i][0b11][j], dp[i-1][0b01][j] + 2);
                }
            }
        }

        int ans = INF;
        ans = min(ans, dp[N-2][0b11][0b11]);
        ans = min(ans, dp[N-2][0b11][0b00] + 2);
        ans = min(ans, dp[N-2][0b11][0b01] + 1);
        ans = min(ans, dp[N-2][0b11][0b10] + 1);
        if(arr[0][N-1] + arr[1][N-1] <= W) ans = min(ans, dp[N-2][0b11][0b00] + 1);
        if(arr[0][N-2] + arr[0][N-1] <= W && arr[1][N-2] + arr[1][N-1] <= W) ans = min(ans, dp[N-2][0b00][0b00] + 2);
        if(arr[0][N-2] + arr[0][N-1] <= W) {
            ans = min(ans, dp[N-2][0b10][0b10] + 1);
            ans = min(ans, dp[N-2][0b10][0b00] + 2);
        }
        if(arr[1][N-2] + arr[1][N-1] <= W) {
            ans = min(ans, dp[N-2][0b01][0b01] + 1);
            ans = min(ans, dp[N-2][0b01][0b00] + 2);
        }

        cout << ans << "\n";
    }
}