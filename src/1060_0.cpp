#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF = 1e18;
const int MAXL = 55;

int l, n, s[MAXL];

ll compute_luckyset(int value)
{
    auto right = lower_bound(s, s + l, value);
    if(right == s + l)
    {
        return INF;
    }

    auto left = right;
    if(*right != value)
    {
        left--;
    }

    ll diff = *right - *left - 1;
    ll x = value - *left;
    return x * (diff - x + 1) - 1;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> l;
    l++; // dummy s[0] = 0
    for(int i = 1; i < l; i++)
    {
        cin >> s[i];
    }
    cin >> n;

    sort(s, s + l);

    // lucky set, value
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    map<ll, bool> visited;
    if(s[1] != 1)
        pq.emplace(s[1] - 2, 1);
    visited[0] = true;
    visited[1] = true;
    for(int i = 1; i < l; i++)
    {
        int diff = s[i] - s[i - 1] - 1;
        pq.emplace(0, s[i]);
        visited[s[i]] = true;
    }

    while(n--)
    {
        auto [lucky_set, value] = pq.top(); pq.pop();
        cout << value << " ";

        if(s[l - 1] < value)
        {
            pq.emplace(INF, value + 1);
            continue;
        }

        if(!visited[value - 1])
        {
            pq.emplace(compute_luckyset(value - 1), value - 1);
            visited[value - 1] = true;
        }
        if(!visited[value + 1])
        {
            pq.emplace(compute_luckyset(value + 1), value + 1);
            visited[value + 1] = true;
        }
    }
}