#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500005;
const int MOD = 1000000007;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n;
    int prev = 1;
    int cur;
    int sum = 1;
    int max_h = 0;

    cin >> n;
    cin >> max_h;

    for(int i = 1; i < n; i++)
    {
        int h;
        cin >> h;
        if(max_h < h)
        {
            cur = sum + 1;
            if(cur >= MOD)
            {
                cur -= MOD;
            }
            max_h = h;
        }
        else
        {
            cur = prev;
        }

        sum += cur;
        if(sum >= MOD)
        {
            sum -= MOD;
        }
        prev = cur;
    }

    cout << cur;
}