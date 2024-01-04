#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    vector<unsigned short> v;
    int n;
    int cnt = 0;
    int jinju;
    bool flag = false;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        string loc;
        long long cost;
        cin >> loc >> cost;
        if(flag)
        {
            if(cost > jinju) cnt++;
        }
        else
        {
            if(loc == "jinju")
            {
                cout << cost << "\n";
                jinju = cost;
                flag = true;
            }
            if(cost <= 1000) v.push_back(cost);
            else cnt++;
        }
    }

    for(auto i : v)
    {
        if(i > jinju) cnt++;
    }

    cout << cnt;
}