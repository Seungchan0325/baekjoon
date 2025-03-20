#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll N, M, sum, mx;

int main()
{
    cin >> N;
    cin >> M;
    for(int i = 0; i < M; i++) {
        ll acc = 0, smx = 0;
        ll k;
        string s;
        cin >> s >> k;
        for(auto c : s) {
            if(c == 'F') acc++;
            if(c == 'M') acc--;
            smx = max(smx, acc);
        }
        mx = max({mx, sum + (k-1) * acc + smx, sum + smx});
        sum += k * acc;
    }

    if(sum < 0) cout << "-1\n";
    else cout << max(0LL, mx - sum - 1) << "\n";
}