#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int t; cin >> t;
    while(t--) {
        int n, k;
        cin >> n >> k;
        vector<int> v(n);
        for(auto& i : v) cin >> i;

        bool yes = false;
        for(int i = 1; i <= k; i<<=1) {
            int cnt = 0;
            for(auto& j : v) cnt += j / i;
            if(cnt&1) yes = true;
        }

        if(yes) cout << "1";
        else cout << "0";
    }
}