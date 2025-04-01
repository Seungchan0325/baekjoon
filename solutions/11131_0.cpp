#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t; cin >> t;
    while(t--) {
        int n;
        cin >> n;
        int acc = 0;
        for(int i = 0; i < n; i++) {
            int d; cin >> d;
            acc += d;
        }
        if(acc == 0) cout << "Equilibrium\n";
        if(acc < 0) cout << "Left\n";
        if(acc > 0) cout << "Right\n";
    }
}