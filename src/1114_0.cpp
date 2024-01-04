#include <bits/stdc++.h>

using namespace std;

int L, K, C;
vector<int> pos, parts;

int ComputeCuttingCount(int first_cutting, int max_len)
{
    int sum = 0;
    int cnt = 0;
    int i = 0;
    while(sum != pos[first_cutting]) sum += parts[i++];
    sum = 0;
    for(; i < parts.size(); i++)
    {
        sum += parts[i];
        if(max_len < sum)
        {
            cnt++;
            sum = parts[i];
        }
    }

    return cnt;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> L >> K >> C;

    pos.resize(K);
    for(int i = 0; i < K; i++)
    {
        cin >> pos[i];
    }
    pos.push_back(0);
    pos.push_back(L);
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());

    parts.reserve(pos.size());
    for(int i = 1; i < pos.size(); i++)
    {
        parts.push_back(pos[i] - pos[i - 1]);
    }

    int lo = *max_element(parts.begin(), parts.end()) - 1;
    int hi = L;
    while(lo + 1 < hi)
    {
        int mid = (lo + hi) / 2;
        if(C < ComputeCuttingCount(0, mid)) lo = mid;
        else hi = mid;
    }

    int ans = hi;
    cout << ans << " ";

    lo = 0;
    hi = pos.size();
    while(lo + 1 < hi)
    {
        int mid = (lo + hi) / 2;
        if(C - 1 < ComputeCuttingCount(mid, ans)) lo = mid;
        else hi = mid;
    }
    cout << pos[hi];
}