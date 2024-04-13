#include <bits/stdc++.h>

using namespace std;

const int MAXD = 2005;

bool visited[MAXD][MAXD];
int ans, D1, D2;

int main()
{
    cin >> D1 >> D2;
    for(int d = D1; d <= D2; d++) {
        for(int n = 1; n <= d; n++) {
            int GCD = gcd(d, n);
            if(!visited[n/GCD][d/GCD]) ans++;
            visited[n/GCD][d/GCD] = true;
        }
    }
    cout << ans;
}