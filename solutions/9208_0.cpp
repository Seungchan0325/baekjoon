#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int t;
    cin >> t;
    while(t--) {
        int m, n;
        cin >> m >> n;
        vector<pair<int, int>> v(n);
        for(auto& [s, e] : v) cin >> s >> e;
        for(int i = 0; i < n; i++) {
            auto& [s, e] = v[i];
            if(s <= e) v.emplace_back(s+m, e+m);
            else e += m;
        }
        
        sort(v.begin(), v.end());
        
        int i = 0;
        priority_queue<int, vector<int>, greater<>> pq;
        for(int s = 0; i < v.size() || pq.size(); s++) {
            if(pq.empty() && i < v.size() && s < v[i].first) s = v[i].first;
            while(i < v.size() && v[i].first <= s) {
                pq.emplace(v[i].second);
                i++;
            }
            assert(pq.size());
            int e = pq.top();
            if(e < s) goto NO;
            else pq.pop();
        }

        if(m < n) goto NO;

        YES: cout << "YES\n"; continue;
        NO: cout << "NO\n"; continue;
    }
}