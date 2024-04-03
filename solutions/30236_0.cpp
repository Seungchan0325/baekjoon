#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t; cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<int> a(n);

        for(auto& i : a) {
            cin >> i;
        }

        int bi = 1;
        if(bi == a[0]) bi++;
        for(int i = 1; i < n; i++) {
            bi++;
            if(bi == a[i]) bi++;
        }

        cout << bi << "\n";
    }
}