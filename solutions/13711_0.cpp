#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

int n, p[MAXN], q[MAXN];

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) {
        int x; cin >> x;
        p[x] = i;
    }
    for(int i = 1; i <= n; i++) {
        int x; cin >> x;
        q[x] = i;
    }

    vector<pair<int, int>> v;
    for(int i = 1; i <= n; i++) {
        v.push_back({p[i], q[i]});
    }
    sort(v.begin(), v.end());

    vector<int> lis;
    for(auto [_, i] : v) {
        if(lis.empty() || lis.back() < i) lis.push_back(i);
        else *lower_bound(lis.begin(), lis.end(), i) = i;
    }
    cout << lis.size() << "\n";
}