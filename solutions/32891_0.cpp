#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x, y;
    auto operator <=> (const Point& rhs) const = default;
};

vector<Point> a(5);

int main()
{
    for(int i = 0; i < 5; i++) {
        cin >> a[i].x >> a[i].y;
    }

    int ans = 0;
    for(int i = 0; i < 20; i++) {
        if(a.size() == 1) break;
        sort(a.begin(), a.end());
        ans += a[1].x - a[0].x;
        a[0].x = a[1].x;
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
        for(int j = 0; j < a.size(); j++) {
            auto [x, y] = a[j];
            a[j].x = y;
            a[j].y = -x;
        }
    }

    if(a.size() == 1) {
        cout << ans << "\n";
    } else {
        int l = a[0].x, r = a[0].x, b = a[0].y, t = a[0].y;
        for(auto [x, y] : a) {
            l = min(l, x);
            r = max(r, x);
            b = min(b, y);
            t = max(b, t);
        }
        ans += 2 * (r - l + t - b);
        for(auto [x, y] : a) {
            if(l != x && r != x && b != y && t != y) {
                ans += min(r-l, t-b);
            }
        }
        cout << ans;
    }
}