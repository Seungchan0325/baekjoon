#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, d;
    cin >> n >> d;
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        int j = i;
        while(j) {
            if(j%10 == d) ans++;
            j/=10;
        }
    }
    cout << ans;
}