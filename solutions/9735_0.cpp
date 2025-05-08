#pragma GCC optimize("O2")

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

vector<long double> solve(ll a, ll b, ll c)
{
    ll D = b * b - 4 * a * c;
    if(D < 0) return {};
    if(D == 0) return {(long double)(-b) / (2*a)};
    return {(long double)(-b - sqrt(D)) / (2*a), (long double)(-b + sqrt(D)) / (2*a)};
}

int main()
{
    int t;
    cin >> t;
    while(t--) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        auto f = [&](long double x)
        {
            return a * x * x * x + b * x * x + c * x + d;
        };
        for(ll x = -1'000'000; x <= 1'000'000; x++) {
            if(f(x) == 0) {
                auto ans = solve(a, a*x+b, (a*x+b)*x+c);
                ans.push_back(x);
                sort(ans.begin(), ans.end());
                ans.erase(unique(ans.begin(), ans.end(), [](long double a, long double b){return abs(a-b)<=1e-4;}), ans.end());
                for(auto i : ans) cout << fixed << setprecision(4) << i << " ";
                break;
            }
        }
        cout << "\n";
    }
}