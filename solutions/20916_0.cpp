#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    vector<int> good;
    good.push_back(202021);
    good.push_back(20202021);
    for(int i = 0; i <= 90000; i += 10000) {
        good.push_back(202002021 + i);
    }
    int T; cin >> T;
    while(T--) {
        int n;
        cin >> n;
        vector<int> v(n);
        for(auto& i : v) cin >> i;
        sort(v.begin(), v.end());
        long long ans = 0;
        for(int i = 0; i < good.size(); i++) {
            int p = n-1;
            int q = n-1;
            for(int j = 0; j < n; j++) {
                int target = good[i] - v[j];
                while(p >= 0 && v[p] >= target) p--;
                while(q >= 0 && v[q] > target) q--;
                ans += q - p;
            }
        }
        cout << ans/2 << "\n";
    }
}