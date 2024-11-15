#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;
    cin >> T;
    while(T--) {
        long long A, B, C;
        cin >> A >> B >> C;
        long long S = A + 2 * B + 3 * C;

        if(S&1LL) cout << "No\n";
        else if(C > A) cout << "No\n";
        else if((A-C) % 2LL == 1LL) cout << "No\n";
        // else if(A == C && (B&1) && (~C&1)) cout << "No\n";
        else if(A == 0 && (B&1)) cout << "No\n";
        else {
            cout << "Yes\n";
        }
    }
}