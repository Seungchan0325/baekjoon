#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<int> v(N);
    for(auto& i : v) cin >> i;
    sort(v.begin(), v.end());
    int ans = v[N-1] - v[0];
    for(int i = 1; i < N; i++) ans += v[i] - v[i-1];
    cout << ans;
}