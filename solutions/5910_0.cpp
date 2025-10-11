#include <bits/stdc++.h>

using namespace std;

int N;

int main()
{
    cin >> N;
    vector<pair<int, int>> v(N);
    for(auto& [u, d] : v) cin >> u >> d;
    sort(v.begin(), v.end(), [](pair<int, int> a, pair<int, int> b){return min(a.first, a.second)<min(b.first, b.second);});
    vector<pair<int, int>> a, b;
    for(auto [u, d] : v) {
        if(u < d) a.push_back({u, d});
        else b.push_back({u, d});
    }
    a.insert(a.end(), b.rbegin(), b.rend());
    v = a;
    int t1 = 0;
    int t2 = 0;
    for(auto [u, d] : v) {
        t1 += u;
        t2 = max(t2, t1) + d;
    }
    cout << t2 << "\n";
}