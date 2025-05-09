#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int t;
    cin >> t;
    while(t--) {
        int n, m;
        cin >> n >> m;
        if(n > m) swap(n, m);
        if(n == 1 && m == 3) cout << "2 5\n";
        else if(n == m) cout << n << " " << 3 << "\n";
        else if(m <= 2*n) cout << n << " " << 7 << "\n";
        else {
            cout << n+1 << " ";
            if(m <= 2*n+2) cout << 7 << "\n";
            else cout << 7 + 2 * (m - (2*n + 2)) << "\n";
        }
    }
}