#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n;
    cin >> n;

    int ans = 0;
    vector<int> v;
    v.push_back(-INF);
    for(int i = 0; i < n; i++) {
        int value; cin >> value;
        if(v.back() < value) {
            v.push_back(value);
            ans++;
        } else {
            *lower_bound(v.begin(), v.end(), value) = value;
        }
    }

    cout << ans;
}