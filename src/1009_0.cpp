#include <bits/stdc++.h>

using namespace std;

int main() {
    int t; cin >> t;
    while(t--) {
        int a, b, x = 1; cin >> a >> b;
        for(int i = 0; i < b; i++) {
            x *= a;
            x %= 10;
        }
        if(x == 0) x = 10;
        cout << x << '\n';
    }
}