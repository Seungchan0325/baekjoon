#include <bits/stdc++.h>

using namespace std;

int W, S, X, Y, H[10101][101], s[101], ss[101];

int main()
{
    cin >> W >> S >> X >> Y;
    for(int i = 1; i <= W; i++) {
        for(int j = 1; j <= X; j++) cin >> H[i][j];
    }
    for(int i = 1; i <= S; i++) {
        for(int j = 1; j <= X; j++) cin >> s[j];
        for(int j = 1; j <= X; j++) ss[j] = max(ss[j], s[j]);
    }
    for(int i = 1; i <= W; i++) {
        for(int j = 1; j <= X; j++) {
            cout << min(H[i][j], Y - ss[j]) << " ";
        }
        cout << "\n";
    }
}