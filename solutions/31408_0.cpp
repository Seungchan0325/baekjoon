#include <bits/stdc++.h>

using namespace std;

int cnt[101010];

int main()
{
    int n; cin >> n;
    int mx = 0;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        mx = max(mx, ++cnt[x]);
    }
    if(mx <= (n+1)/2) cout << "YES";
    else cout << "NO\n";
}