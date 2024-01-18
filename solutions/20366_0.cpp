#include <bits/stdc++.h>

using namespace std;

const int INF = INT_MAX;
const int MAXN = 605;

int n, h[MAXN];
vector<tuple<int, int, int>> v;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        cin >> h[i];
    }

    sort(h, h + n);

    int ans = INF;
    for(int i = 0; i < n - 2; i++)
    {
        vector<int> v;
        v.reserve(n * n / 2);
        for(int j = i + 1; j < n; j++)
        {
            for(int k = j + 1; k < n; k++)
            {
                v.push_back(h[k] - h[j]);
            }
        }
        sort(v.begin(), v.end());
        for(int j = 0; j < i; j++)
        {
            int target = h[i] - h[j];
            int lo = 0, hi = v.size() - 1;
            while(lo + 1 < hi)
            {
                int mid = (lo + hi) / 2;
                if(v[mid] < target) lo = mid;
                else hi = mid;
            }

            ans = min({abs(target - v[lo]), abs(target - v[hi]), ans});
        }
    }

    cout << ans;
}