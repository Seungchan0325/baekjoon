#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N, L;
    cin >> N >> L;

    bool exist = false;
    for(int l = L; l <= 100; l++) {
        if(N < l*(l-1)/2) break;
        if((N-l*(l-1)/2) % l == 0) {
            exist = true;
            for(int i = 0; i < l; i++) {
                cout << (N-l*(l-1)/2) / l + i << " ";
            }
            break;
        }
    }

    if(!exist) cout << -1;
}