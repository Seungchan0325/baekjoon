#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    vector<pair<int, int>> v;
    for(int h = 1; h <= 150; h++) {
        for(int w = h+1; w <= 150; w++) {
            v.emplace_back(w, h);
        }
    }
    sort(v.begin(), v.end(), [](pair<int, int> a, pair<int, int> b){
        int da = a.first * a.first + a.second * a.second;
        int db = b.first * b.first + b.second * b.second;
        if(da != db) return da < db;
        return a.second < b.second;
    });

    while(true) {
        int w, h;
        cin >> h >> w;
        if(w == 0 && h == 0) break;
        auto it = upper_bound(v.begin(), v.end(), make_pair(w, h), [](pair<int, int> a, pair<int, int> b){
        int da = a.first * a.first + a.second * a.second;
        int db = b.first * b.first + b.second * b.second;
        if(da != db) return da < db;
        return a.second < b.second;
        });
        cout << it->second << " " << it->first << "\n";
    }
}