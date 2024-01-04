#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, l, r;
    cin >> n >> l >> r;
    vector<int> a(n);
    for(auto& i : a)
    {
        cin >> i;
    }

    long long ans = 0;
    for(int taken = 1; taken < (1<<n); taken++)
    {
        int cnt = 0;
        long long mul = 1;
        for(int i = 0; i < n; i++)
        {
            if(!(taken & (1<<i))) continue;
            mul = lcm(mul, a[i]);
            cnt++;
        }

        if(cnt & 1) ans += r / mul - (l - 1) / mul;
        else ans -= r / mul - (l - 1) / mul;
    }
    cout << ans;
}