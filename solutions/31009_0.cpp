#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    map<string, int> m;
    for(int i = 0; i < n; i++)
    {
        string loc;
        int cost;
        cin >> loc >> cost;
        m[loc] = cost;
    }
    cout << m["jinju"] << "\n";
    int cnt = 0;
    for(auto [loc, cost] : m)
    {
        if(cost > m["jinju"]) cnt++;
    }
    cout << cnt;
}