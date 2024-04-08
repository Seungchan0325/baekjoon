#include <bits/stdc++.h>

using namespace std;

const int MAXC = 200005;

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int C;
bool a[MAXC][4];

int main()
{
    cin >> C;
    for(int i = 1; i <= C; i++) {
        cin >> a[i][1];
    }
    for(int i = 1; i <= C; i++) {
        cin >> a[i][2];
    }
    int ans = 0;
    for(int i = 1; i <= 2; i++) {
        for(int j = 1; j <= C; j++) {
            if(a[j][i]) {
                ans += 3;
                for(int k = 0; k < 4; k++) {
                    if(j % 2 == 0 && k % 2 == 0) continue;
                    if(a[j+dx[k]][i+dy[k]]) ans--;
                }
            }
        }
    }
    cout << ans;
}