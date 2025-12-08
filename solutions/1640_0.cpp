#include <bits/stdc++.h>

using namespace std;

int n, m, A[1010][1010];

int main()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            char c; cin >> c;
            A[i][j] = c - '0';
        }
    }

    int rowEven, rowOdd, colEven, colOdd;
    rowEven = rowOdd = colEven = colOdd = 0;

    for(int i = 1; i <= n; i++) {
        int c = 0;
        for(int j = 1; j <= m; j++) {
            c ^= A[i][j];
        }
        if(c) rowOdd++;
        else rowEven++;
    }
    for(int j = 1; j <= m; j++) {
        int c = 0;
        for(int i = 1; i <= n; i++) {
            c ^= A[i][j];
        }
        if(c) colOdd++;
        else colEven++;
    }

    int ans = 1e9;

    if(rowOdd&1) {
        if(~colEven&1) ans = min(colEven + rowOdd, ans);
    } else {
        if(~colOdd&1) ans = min(colOdd + rowOdd, ans);
    }

    if(rowEven&1) {
        if(colEven&1) ans = min(colEven + rowEven, ans);
    } else {
        if(colOdd&1) ans = min(colOdd + rowEven, ans);
    }

    cout << ans << "\n";
}