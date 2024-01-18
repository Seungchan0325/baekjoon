#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
const int MAXXY = 100001;

int n, x[MAXN], y[MAXN], xs[MAXXY], ys[MAXXY];

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        xs[x[i]]++;
        ys[y[i]]++;
    }

    long long ans = 0;
    for(int i = 0; i < n; i++) {
        ans += (long long)(xs[x[i]]-1) * (ys[y[i]]-1);
    }
    cout << ans;
}