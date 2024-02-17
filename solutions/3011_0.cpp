#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;

int main()
{
    int n, a, b;
    cin >> n;
    vector<int> p(n);
    for(int i = 0; i < n; i++) {
        cin >> p[i];
    }
    cin >> a >> b;

    if(!(a & 1)) a++;
    if(!(b & 1)) b--;

    int ans = -1;
    int max_v = -1;
    sort(p.begin(), p.end());
    auto it = lower_bound(p.begin(), p.end(), a);
    int tmp = INF;
    if(it != p.end()) tmp = min(*it - a, tmp);
    if(it != p.begin()) tmp = min(a - *(it-1), tmp);
    if(tmp < INF && tmp > max_v) {
        max_v = tmp;
        ans = a;
    }

    it = lower_bound(p.begin(), p.end(), b);
    tmp = INF;
    if(it != p.end()) tmp = min(*it - b, tmp);
    if(it != p.begin()) tmp = min(b - *(it-1), tmp);
    if(tmp < INF && tmp > max_v) {
        max_v = tmp;
        ans = b;
    }

    for(int i = 1; i < n; i++) {
        int mid = (p[i-1] + p[i]) / 2;
        if(mid & 1) {
            if(a <= mid && mid <= b) {
                // ans = max(p[i] - mid, ans);
                int c = p[i] - mid;
                if(c > max_v) {
                    max_v = c;
                    ans = mid;
                }
            }
        } else {
            if(a <= mid - 1 && mid - 1 <= b) {
                // ans = max(min(p[i] - (mid - 1), (mid - 1) - p[i-1]), ans);
                int c = min(p[i] - (mid - 1), (mid - 1) - p[i-1]);
                if(c > max_v) {
                    max_v = c;
                    ans = mid - 1;
                }
            }
            if(a <= mid + 1 && mid + 1 <= b) {
                // ans = max(min(p[i] - (mid + 1), (mid + 1) - p[i-1]), ans);
                int c = min(p[i] - (mid + 1), (mid + 1) - p[i-1]);
                if(c > max_v) {
                    max_v = c;
                    ans = mid + 1;
                }
            }
        }
    }
    assert(ans != -1);
    assert(max_v != -1);
    cout << ans;
}