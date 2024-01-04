#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> a, b;

int main() {
    cin >> n;
    a.resize(n); b.resize(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];

    sort(a.begin(), a.end());
    sort(b.begin(), b.end(), greater<>());

    int ans = 0;
    for(int i = 0; i < n; i++) {
        ans += a[i] * b[i];
    }

    cout << ans;
}