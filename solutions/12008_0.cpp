#include <bits/stdc++.h>

using namespace std;

int n, a[1<<19];
map<int, vector<pair<int, int>>> m;

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        m[a[i]].push_back(pair(i, i));
    }

    int ans = 0;
    for(int i = 1; i < 60; i++) {
        auto v = m[i];
        auto vv = m[i];
        sort(v.begin(), v.end());
        sort(vv.begin(), vv.end(), [](pair<int, int> a, pair<int, int> b){
            return a.second < b.second;
        });

        int j = 0;
        int k = 0;
        for(int j = 0; j < vv.size(); j++) {
            while(k < v.size() && v[k].first <= vv[j].second) {
                k++;
            }

            if(k < v.size()) {
                if(vv[j].second + 1 == v[k].first) {
                    m[i+1].emplace_back(vv[j].first, v[k].second);
                }
            }
        }

        if(m[i].size()) ans = i;
    }
    cout << ans;
}