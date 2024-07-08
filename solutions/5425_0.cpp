#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll mystoi(string s)
{
    if(s.empty()) return 0;
    return stoll(s);
}

ll f(string N)
{
    ll ans = 0;
    for(int i = 0; i < N.size(); i++) {
        ll prv = mystoi(N.substr(0, i));
        ll r = pow(10, N.size() - i - 1);
        for(int j = 0; j < 10; j++) {
            if(j < N[i]-'0') {
                ans += (prv+1) * r * j;
            }
            else if(j == N[i]-'0') {
                ans += (prv * r) * j;
                // if(N.substr(i+1).size()) {
                ans += (mystoi(N.substr(i+1)) + 1) * j;
                // }
            }
            else {
                ans += (prv) * (r) * j;
            }
        }
    }

    return ans;
}

int main()
{
    int tc;
    cin >> tc;
    while(tc--) {
        ll a, b;
        cin >> a >> b;
        cout << f(to_string(b)) - f(to_string(max(0LL, a-1))) << "\n";
    }
}