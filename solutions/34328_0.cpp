#include <bits/stdc++.h>

using namespace std;

bool chk[505050];

int main()
{
    unsigned n;
    cin >> n;
    if(n == 1) {
        cout << "1\n";
    } else if(n == 2) {
        cout << "1 2\n";
    } else if(has_single_bit(n+2)) {
        for(int i = 1; i <= n; i++) cout << i << " ";
        cout << "\n";
    } else {
        cout << "-1\n";
    }
}