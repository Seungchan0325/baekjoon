#include <bits/stdc++.h>

using namespace std;

const string KSA = "KSA";

int main()
{
    string X;
    cin >> X;

    int ans = 987654321;
    for(int tprv = 0; tprv < 3; tprv++) {
        int prv = tprv;
        int len = 0;
        for(int i = 0; i < X.size(); i++) {
            if(X[i] == KSA[(prv+1)%3]) {
                prv = (prv+1)%3;
                len++;
            }
        }

        int cand = X.size() - len;

        int fi = (tprv+1)%3;
        if(fi == 1) len++, cand++;
        else if(fi == 2) len += 2, cand += 2;

        if(len > X.size()) {
            cand += len - X.size();
        } else {
            cand += X.size() - len;
        }

        ans = min(cand, ans);
    }

    cout << ans;
}