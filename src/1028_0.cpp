#include <bits/stdc++.h>

using namespace std;

const int MAXNM = 800;

int n, m, right_up[MAXNM][MAXNM], right_down[MAXNM][MAXNM], left_up[MAXNM][MAXNM], left_down[MAXNM][MAXNM];
char shape[MAXNM][MAXNM];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            cin >> shape[i][j];

    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++)
        if(shape[i][j] == '1') right_down[i][j] = right_down[i-1][j-1] + 1;

    for(int i = 1; i <= n; i++) for(int j = m; j >= 1; j--)
        if(shape[i][j] == '1') left_down[i][j] = left_down[i-1][j+1] + 1;

    for(int i = n; i >= 1; i--) for(int j = 1; j <= m; j++)
        if(shape[i][j] == '1') right_up[i][j] = right_up[i+1][j-1] + 1;

    for(int i = n; i >= 1; i--) for(int j = m; j >= 1; j--)
        if(shape[i][j] == '1') left_up[i][j] = left_up[i+1][j+1] + 1;

    int ans = 0;
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) {
        if(shape[i][j] == '1') {
            int size = 1;
            int left = j;
            int right = j;
            int up = i;
            int down = i;
            while(true) {
                if(m < right || up < 1 || n < down) break;

                int mid = (left + right) / 2;
                if(size <= min({right_up[up][mid], right_down[down][mid], left_up[up][mid], left_down[down][mid]}))
                    ans = max(size, ans);

                size++;
                right += 2;
                up--;
                down++;
            }
        }
    }

    cout << ans;
}