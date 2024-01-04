#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    for(int i = 0; i < k; i++) {
        int v; cin >> v;
        float p = 100 * v / n;
        if(0 <= p && p <= 4) cout << 1 << " ";
        else if(p <= 11) cout << 2 << " ";
        else if(p <= 23) cout << 3 << " ";
        else if(p <= 40) cout << 4 << " ";
        else if(p <= 60) cout << 5 << " ";
        else if(p <= 77) cout << 6 << " ";
        else if(p <= 89) cout << 7 << " ";
        else if(p <= 96) cout << 8 << " ";
        else cout << 9 << " ";
    }
}
Unknown problem. sumbmit number: 67047668