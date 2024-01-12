#include <bits/stdc++.h>

using namespace std;

int main() 
{
    int n, k;
    double ps[20005];
    cin >> n >> k;
    for(int i = 0; i < n; i++) cin >> ps[i];
    sort(ps, ps + n);
    for(int i = 0; i < n; i++) ps[n + i] = ps[i] + 360.0f;

    int ans = 9876541;
    for(int i = 0; i < n; i++) {
        int min_v = 987654321;
        int max_v = 0;

        double p = ps[i] - 0.0001;
        int prev = i;
        for(int j = 0; j < k; j++) {
            p += 360.0 / k;
            int next = upper_bound(ps, ps + 2 * n, p) - ps;
            min_v = min(min_v, next - prev);
            max_v = max(max_v, next - prev);
            prev = next;
        }
        ans = min(max_v - min_v, ans);
    }
    cout << ans;
}