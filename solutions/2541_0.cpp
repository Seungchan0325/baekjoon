#include <bits/stdc++.h>

using namespace std;

const int MXX = 100;

int a, b;
bool A[MXX][MXX];

void dfs(int x, int y)
{
    if(x < 0 || x >= MXX || y < 0 || y >= MXX || A[x][y]) return;
    A[x][y] = true;
    dfs(x+1, y+1);
    if(x%2==0 &&y%2==0) dfs(x/2, y/2);
    for(int z= 0 ; z<MXX; z++) {
        if(A[y][z]) dfs(x, z);
        if(A[z][x]) dfs(z, y);
    }
}

int main()
{
    cin >> a >> b;
    // dfs(a, b);
    // for(int i = MXX-1; i >= 0; i--) {
    //     for(int j =0; j < 100; j++)  {
    //         if(i == b && j == a) cout << "#";
    //         else if(A[j][i]) cout << "*";
    //         else cout << ".";
    //     }
    //     cout << "\n";
    // }

    
    // for(int i = MXX-1; i >= 0; i--) {
    //     for(int j =0; j < 100; j++) {
    //         if(A[j][i])
    //             cout << j << " " << i << "\n";
    //     }
    //     cout << "\n";
    // }

    // cin >> a >> b;
    for(int i = 0; i < 5; i++) {
        int x, y; cin >> x >> y;
        
        // cout << "---\n";
        if(a == b) {
            if(x == y) cout << "Y\n";
            else cout << "N\n";
        } else if(a < b) {
            x -= min(a, b);
            y -= min(a, b);
            int diff = abs(a-b);
            while(~diff&1) diff>>=1;
            if((y-x) % diff == 0 && y-x > 0) cout << "Y\n";
            else cout << "N\n";
        } else {
            x -= min(a, b);
            y -= min(a, b);
            int diff = abs(a-b);
            while(~diff&1) diff>>=1;
            if((x-y) % diff == 0 && x-y > 0) cout << "Y\n";
            else cout << "N\n";
        }
        // if(A[x][y]) cout << "Y\n";
        // else cout << "N\n";
    }
}