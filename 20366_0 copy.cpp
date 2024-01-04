#include <bits/stdc++.h>

using namespace std;

const int INF = INT_MAX;
const int MAXN = 600;

int n, h[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        cin >> h[i];
    }

    vector<tuple<int, int, int>> v;
    v.reserve(n * n / 2);
    for(int i = 0; i < n; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            v.emplace_back(h[i] + h[j], i, j);
        }
    }

    sort(v.begin(), v.end());

    int ans = INF;
    for(int i = 0; i < v.size(); i++)
    {
        auto [sum1, i1, j1] = v[i];
        for(int j = i + 1; j < v.size(); j++)
        {
            auto [sum2, i2, j2] = v[j];
            if(i1 == i2 || i1 == j2 || j1 == i2 || j1 == j2)
            {
                continue;
            }
            ans = min(abs(sum1 - sum2), ans);
            break;
        }
    }

    cout << ans;
}