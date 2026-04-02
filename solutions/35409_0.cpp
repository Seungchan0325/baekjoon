#include <bits/stdc++.h>

using namespace std;

int submit[][2] = {
    {630, 900},
    {950, 1000},
    {1050, 1100},
    {1150, 1200},
    {1250, 1350},
    {1440, 1450},
    {1540, 1550},
    {1640, 2250},
};

int main()
{
    int H, M;
    cin >> H >> M;
    int T = H * 100 + M;
    bool ans = false;
    for(int i = 0; i < 8; i++) {
        if(submit[i][0] <= T && T <= submit[i][1]) ans = true;
    }
    if(ans) cout << "Yes\n";
    else cout << "No\n";
}