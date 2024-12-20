#include <bits/stdc++.h>

using namespace std;

int c[55];

int main()
{
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        int a;
        cin >> a;
        c[a]++;
    }

    for(int i = 50; i >= 0; i--) {
        if(c[i] == i) {
            cout << i;
            return 0;
        }
    }
    cout << "-1";
}