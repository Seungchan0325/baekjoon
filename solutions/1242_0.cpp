#include <bits/stdc++.h>

using namespace std;


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k, m;
    cin >> n >> k >> m;

    m--;
    int cnt = 1;
    int cur = 0;
    while(true)
    {
        cur = (cur + k - 1) % n;

        if(cur == m)
        {
            cout << cnt << "\n";
            break;
        }

        n--;
        if(cur < m) m--;
        cnt++;
    }
}