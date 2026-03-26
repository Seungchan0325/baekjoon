#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    if(k == 0) {
        for(int i = 0; i < n; i++) cout << "0 ";
    } else if(k == 1) {
        for(int i = 0; i < n; i++) cout << "1 ";
    } else if(k == 2) {
        if(n == 1) cout << "-1";
        else {
            for(int i = 1; i < n; i++) cout << "0 ";
            cout << "2";
        }
    } else {
        for(int i = 0; i < n; i++) {
            if(i+1 < k) cout << i << " ";
            else cout << "0 ";
        }
    }
}