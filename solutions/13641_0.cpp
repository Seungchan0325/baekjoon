#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n;
    while(cin >> n) {
        vector<pair<int, int>> v(n);
        for(int i = 0; i < n; i++) {
            int a; cin >> a;
            v[a-1].first = i;
        }
        for(int i = 0; i < n; i++) {
            int a; cin >> a;
            v[a-1].second = i;
        }
        sort(v.begin(), v.end());
        int ans = 0;
        for(int i = 0; i < n; i++) {
            for(int j = i+1; j < n; j++) {
                if(v[i].second > v[j].second) {
                    ans++;
                }
            }
        }
        cout << ans << "\n";
    }
}