#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300005;
const int MOD = 1000000007;

int n, a[MAXN], cnt[30];

int main()
{
    cin >> n;
    int and_a = 0;
    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
        and_a &= a[i];
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < 30; j++)
        {
            if(!(and_a & (1<<j)) && (a[i] & (1<<j)))
            {
                cnt[j]++;
                a[i] -= 1<<j;
            }
        }
    }

    sort(a, a + n, greater<int>());

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < 30; j++)
        {
            if(!(a[i] & (1<<j)) && cnt[j] > 0)
            {
                a[i] += 1<<j;
                cnt[j]--;
            }
        }
    }

    long long ans = 1;
    for(int i = 0; i < n; i++)
    {
        ans *= a[i];
        ans %= MOD;
    }

    cout << ans;
}