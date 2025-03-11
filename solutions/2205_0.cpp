#include <bits/stdc++.h>

using namespace std;

bool chk[1<<16];

int main()
{
    int n;
    cin >> n;
    vector<int> ans(n+1);
    int p = 1<<15;
    for(int i = 1; i <= n; i++) chk[i] = true;
    for(int i = n; i >= 1; i--) {
        while(!chk[p-i]) p /= 2;
        ans[i] = p-i;
        chk[p-i] = false;
    }
    for(int i = 1; i <= n; i++) cout << ans[i] << "\n";
}