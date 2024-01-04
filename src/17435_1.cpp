#include <bits/stdc++.h>

using namespace std;

const unsigned int MAXM = 200000;
const unsigned int LG_N = 20;

unsigned int m, q, f[LG_N+1][MAXM];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> m;
    for(unsigned int i = 1; i <= m; i++)
    {
        cin >> f[1][i];
    }

    for(unsigned int n = 2; n <= LG_N; n++)
    {
        for(unsigned int i = 1; i <= m; i++)
        {
            f[n][i] = f[n - 1][f[n - 1][i]];
        }
    }

    cin >> q;
    while(q--)
    {
        unsigned int n, x;
        cin >> n >> x;

        unsigned int ans = x;
        for(unsigned int i = 1; n != 0; i++)
        {
            if(n & 1)
                ans = f[i][ans];
            n >>= 1;
        }

        cout << ans << "\n";
    }
}