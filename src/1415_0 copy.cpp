#include <bits/stdc++.h>

using namespace std;

bool is_prime[500005];

int main()
{
    memset(is_prime, 1, sizeof(is_prime));

    is_prime[0] = is_prime[1] = false;
    for(long long i = 2; i < 500000; i++)
    {
        if(!is_prime[i])
        {
            continue;
        }

        for(long long j = i + i; j < 500000; j += i)
        {
            is_prime[j] = false;
        }
    }

    long long n;
    cin >> n;
    vector<long long> cost(n);
    for(auto& i : cost)
    {
        cin >> i;
    }

    sort(cost.begin(), cost.end());
    vector<long long> costs;
    vector<long long> cnts;
    // dummy
    costs.push_back(-1);
    cnts.push_back(-1);
    for(auto it = cost.begin(); it != cost.end();)
    {
        costs.push_back(*it);
        auto next = upper_bound(cost.begin(), cost.end(), *it);
        cnts.push_back(next - it);
        it = next;
    }

    long long sum = accumulate(cost.begin(), cost.end(), 0);
    vector<vector<long long>> dp(2, vector<long long>(sum + 1));
    dp[0][0] = 1;
    for(long long i = 1; i < costs.size(); i++)
    {
        dp[i%2] = vector<long long>(sum + 1);
        for(long long j = 0; j <= cnts[i]; j++)
        {
            for(long long k = 0; k <= sum; k++)
            {
                if(0 <= k - costs[i] * j)
                {
                    dp[i%2][k] += dp[(i-1)%2][k - costs[i] * j];
                }
            }
        }
    }
    
    long long cnt = 0;
    for(long long i = 0; i <= sum; i++)
    {
        if(is_prime[i])
        {
            cnt += dp[(costs.size()-1)%2][i];
        }
    }
    cout << cnt;
}