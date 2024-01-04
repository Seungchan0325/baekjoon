#include <bits/stdc++.h>

using namespace std;

const int MAXN = 55;

int n, arr[MAXN][MAXN], psum[MAXN][MAXN];
vector<int> v2[MAXN][MAXN], v1[MAXN][MAXN];

// x1 <= x2 && y1 <= y2;
int gridSum(int y1, int x1, int y2, int x2)
{
    int ret = psum[y2][x2];
    if(0 < x1) ret -= psum[y2][x1-1];
    if(0 < y1) ret -= psum[y1-1][x2];
    if(0 < x1 && 0 < y1) ret += psum[y1-1][x1-1];
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            cin >> arr[i][j];
        }
    }

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            psum[i][j] = psum[i-1][j] + psum[i][j-1] - psum[i-1][j-1] + arr[i][j];
        }
    }

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            for(int k = 1; k <= i; k++)
            {
                for(int l = j; l <= n; l++)
                {
                    v1[i][j].push_back(gridSum(k, j, i, l));
                }
            }
            sort(v1[i][j].begin(), v1[i][j].end());

            for(int k = i; k <= n; k++)
            {
                for(int l = j; l <= n; l++)
                {
                    v2[i][j].push_back(gridSum(i, j, k, l));
                }
            }
            sort(v2[i][j].begin(), v2[i][j].end());
        }
    }

    int ans = 0;

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            for(int k = i; k <= n; k++)
            {
                for(int l = 1; l <= j; l++)
                {
                    int sum = gridSum(i, l, k, j);
                    auto& vv = v1[i-1][j+1];
                    ans += upper_bound(vv.begin(), vv.end(), sum) - lower_bound(vv.begin(), vv.end(), sum);
                }
            }
        }
    }

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            for(int k = 1; k <= i; k++)
            {
                for(int l = 1; l <= j; l++)
                {
                    int sum = gridSum(k, l, i, j);
                    auto& vv = v2[i+1][j+1];
                    ans += upper_bound(vv.begin(), vv.end(), sum) - lower_bound(vv.begin(), vv.end(), sum);
                }
            }
        }
    }

    cout << ans;
}