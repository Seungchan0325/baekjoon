#include <bits/stdc++.h>

using namespace std;

int cnt[202020];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    string A, B;
    cin >> A;
    cin >> B;

    int s = 0;
    for(auto c : A) {
        if(c == '(') s++;
        else s--;
        if(s < 0) break;
        cnt[s]++;
    }
    long long ans = 0;
    int sum = 0;
    int mn = 0;
    for(auto c : B) {
        if(c == '(') sum++;
        else sum--;
        mn = min(mn, sum);
        if(sum <= 0 && mn-sum >= 0) {
            ans += cnt[-sum];
        }
    }

    cout << ans << "\n";
}