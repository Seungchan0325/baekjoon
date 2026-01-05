#include <bits/stdc++.h>

using namespace std;

int n, pi[55], cnt[55], now[55], d[55][1010];

int main()
{
    cin >> n;
    vector<array<int, 3>> v;
    for(int i = 1; i < n; i++) {
        for(int j = 1; ; j++) {
            int k; cin >> k;
            if(k == 0) break;
            d[i][k] = j;
            v.push_back({k, i, 0});
        }
    }
    sort(v.begin(), v.end());
    for(int i = 1; i <= n; i++) pi[i] = i;
    for(auto i : v) swap(pi[i[1]], pi[i[1]+1]);
    reverse(v.begin(), v.end());
    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        for(int i = 1; i <= n; i++) now[i] = pi[i];
        for(auto& j : v) {
            if(j[2]) swap(now[j[1]], now[j[1]+1]);
            if(now[j[1]+1] == i && now[j[1]] > i) {
                swap(now[j[1]], now[j[1]+1]);
                j[2] = true;
                cnt++;
            }
        }
    }

    cout << cnt << "\n";
    for(auto j : v) {
        if(j[2] == true) {
            cout << j[1] << " " << d[j[1]][j[0]] << "\n";
        }
    }
}