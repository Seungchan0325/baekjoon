#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Point {
    ll x, y, i;
    bool operator < (const Point rhs) const {
        return pair(x, y) < pair(rhs.x, rhs.y);
    }
};

ll ccw(Point a, Point b, Point c)
{
    ll ret = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    if(ret < 0) return -1;
    if(ret > 0) return 1;
    return 0;
}

struct AngleCompare {
    Point o;
    AngleCompare(Point o) : o(o) {}
    bool operator () (Point a, Point b) {
        return ccw(o, a, b) < 0;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<Point> ps(n);
    for(auto& [x, y, _i] : ps) cin >> x >> y;

    auto o = min_element(ps.begin(), ps.end(), [](Point a, Point b) {return a.y < b.y;}) - ps.begin();
    swap(ps[0], ps[o]);
    sort(ps.begin() + 1, ps.end(), AngleCompare(ps[0]));

    for(int i = 0; i < n; i++) ps[i].i = i;
    vector<vector<int>> up(n, vector<int>(n, -1e9)), dw(n, vector<int>(n, -1e9)), upp(n, vector<int>(n, -1)), dwp(n, vector<int>(n, -1));
    for(int i = 1; i < n; i++) up[0][i] = 1, upp[0][i] = -1;
    for(int i = 1; i < n; i++) {
        vector<Point> left, right;
        for(auto p : ps) {
            if(ccw(ps[0], ps[i], p) < 0) right.push_back(p);
            if(ccw(ps[0], ps[i], p) > 0) left.push_back(p);
        }
        sort(left.begin(), left.end(), AngleCompare(ps[i]));
        sort(right.begin(), right.end(), AngleCompare(ps[i]));

        int k = 0;
        int mx = up[0][i];
        int mxi = 0;
        for(int j = 0; j < right.size(); j++) {
            while(k < left.size() && ccw(ps[i], right[j], left[k]) < 0) {
                // mx = max(mx, up[i][left[k].i]);
                if(mx < up[i][left[k].i]) {
                    mx = up[i][left[k].i];
                    mxi = left[k].i;
                }
                k++;
            }
            dw[right[j].i][i] = mx + 1;
            dwp[right[j].i][i] = mxi;
        }

        k = (int)left.size() - 1;
        mx = -1e9;
        mxi = -1;
        for(int j = (int)right.size()-1; j >= 0; j--) {
            while(k >= 0 && ccw(ps[i], right[j], left[k]) > 0) {
                // mx = max(mx, dw[i][left[k].i]);
                if(mx < dw[i][left[k].i]) {
                    mx = dw[i][left[k].i];
                    mxi = left[k].i;
                }
                k--;
            }
            up[right[j].i][i] = mx + 1;
            upp[right[j].i][i] = mxi;
        }
    }

    int ans = 0;
    int now = 0, prv = -1;
    for(int i = 0; i < n; i++) {
        dw[0][i] = -1e9;
        for(int j = 0; j < n; j++) {
            if(dw[0][i] < up[i][j] + 1) {
                dw[0][i] = up[i][j] + 1;
                dwp[0][i] = j;
            }
        }
        if(ans < dw[0][i]) {
            ans = dw[0][i];
            prv = i;
        }
    }
    if(ans <= 2) {
        cout << "0\n";
        return 0;
    }
    cout << ans << "\n";
    while(prv != -1) {
        cout << ps[now].x << " " << ps[now].y << "\n";
        cout << ps[prv].x << " " << ps[prv].y << "\n";
        int t;
        t = dwp[now][prv];
        now = prv;
        prv = t;
        t = upp[now][prv];
        now = prv;
        prv = t;
    }
}