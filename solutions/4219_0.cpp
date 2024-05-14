#include <bits/stdc++.h>

using namespace std;

const int MAXX = 1005;

int sum[2*MAXX][2*MAXX];

int main()
{
    int t = 0;
    while(true) {
        int dx, dy, n, q;
        cin >> dx >> dy >> n >> q;

        if(dx == 0 && dy == 0 && n == 0 && q == 0) break;

        memset(sum, 0, sizeof(sum));
        for(int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            sum[x - y + dy][x + y]++;
        }

        for(int i = 1; i <= dx + dy; i++) {
            for(int j = 1; j <= dx + dy; j++) {
                sum[i][j] += sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
            }
        }

        printf("Case %d:\n", ++t);

        while(q--) {
            int m;
            cin >> m;
            tuple<int, int, int> ans = {-1, 0, 0};
            for(int i = 1; i <= dx; i++) {
                for(int j = 1; j <= dy; j++) {
                    int x = i - j + dy;
                    int y = i + j;

                    int leftx = max(0, x - m - 1);
                    int lefty = max(0, y - m - 1);
                    int rightx = min(dx + dy, x + m);
                    int righty = min(dx + dy, y + m);
                    int s = sum[rightx][righty] - sum[leftx][righty] - sum[rightx][lefty] + sum[leftx][lefty];

                    ans = max(ans, {s, -j, -i});
                }
            }

            printf("%d (%d,%d)\n", get<0>(ans), -get<2>(ans), -get<1>(ans));
        }
    }
}