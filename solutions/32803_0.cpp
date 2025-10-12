#include <bits/stdc++.h>

using namespace std;

int A[2][5];

int main()
{
    int t; cin >> t;
    while(t--) {
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 5; j++) {
                cin >> A[i][j];
            }
        }
        bool yes = false;
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 5; j++) {
                for(int x = 0; x < 2; x++) {
                    for(int y = 0; y < 5; y++) {
                        if(x == i && y == j) continue;
                        if(A[i][j] == A[x][y]) {
                            if(i != x && j != y) yes = true;
                        }
                    }
                }
            }
        }
        if(yes) cout << "YES\n";
        else cout << "NO\n";
    }
}