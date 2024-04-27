#include <bits/stdc++.h>

using namespace std;

using ll = __int128_t;

const int MAXN = 105;

ll bino[MAXN][MAXN];

// nCr = n-1Cr + n-1Cr-1

int main()
{
    for(int i = 0; i < MAXN; i++) {
        bino[i][0] = 1;
    }

    for(int i = 1; i < MAXN; i++) {
        for(int j = 1; j <= i; j++) {
            bino[i][j] = bino[i-1][j] + bino[i-1][j-1];
        }
    }

    int n, m;
    cin >> n >> m;

    __int128_t ans = bino[n][m];
    stack<int> s;
    while(ans) {
        s.push(ans % 10);
        ans /= 10;
    }

    while(s.size()) cout << s.top(), s.pop();
}