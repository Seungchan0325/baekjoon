#include <bits/stdc++.h>

using namespace std;

const int MAXN = 800;

const int dj[] = {1, 0, -1, 0};
const int di[] = {0, 1, 0, -1};

bool vst[MAXN][MAXN];
int n, a[MAXN][MAXN];

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) vst[i][0] = vst[i][n+1] = vst[0][i] = vst[n+1][i] = true;
    int i = 1;
    int j = 1;
    int cnt = 1;
    int k = 0;
    a[i][j] = cnt++;
    vst[i][j] = true;
    while(cnt <= n*n) {
        while(true) {
            if(vst[i+di[k%4]][j+dj[k%4]]) break;
            i += di[k%4];
            j += dj[k%4];
            a[i][j] = cnt++;
            vst[i][j] = true;
        }
        k++;
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
}