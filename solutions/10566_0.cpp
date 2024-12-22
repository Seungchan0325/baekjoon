#include <bits/stdc++.h>

using namespace std;

struct P {
    int x, y;
    P() : x(0), y(0) {}
    P(int x, int y) : x(x), y(y) {}
    bool operator < (const P& rhs) const {
        return tie(x, y) < tie(rhs.x, rhs.y);
    }
    bool operator == (const P& rhs) const {
        return tie(x, y) == tie(rhs.x, rhs.y);
    }
};

bool inrange(int x, int n)
{
    return 0 <= x && x < n;
}

int ccw(P a, P b, P c)
{
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

vector<P> convex_hull(vector<P> p)
{
    int n = p.size();
    sort(p.begin(), p.end());
    vector<P> up, dw;
    for(int i = 0; i < n; i++) {
        while(up.size() >= 2 && ccw(up.end()[-2], up.end()[-1], p[i]) >= 0) up.pop_back();
        while(dw.size() >= 2 && ccw(dw.end()[-2], dw.end()[-1], p[i]) <= 0) dw.pop_back();
        up.push_back(p[i]);
        dw.push_back(p[i]);
    }

    p = dw;
    for(int i = (int)up.size()-2; i >= 1; i--) p.push_back(up[i]);
    return p;
}

int compute(const vector<P>& v, const vector<vector<char>>& stamp, int dx, int dy)
{
    int l = stamp.size();
    int w = stamp[0].size();
    vector<vector<bool>> in(l, vector<bool>(w, false));
    vector<vector<bool>> out(l, vector<bool>(w, false));

    int ret = 0;
    for(auto p : v) {
        int pxpdx = p.x + dx;
        int pypdy = p.y + dy;
        if(inrange(pxpdx, l) && inrange(pypdy, w) && stamp[pxpdx][pypdy] == '#') {
            out[p.x][p.y] = in[pxpdx][pypdy] = true;
        }
    }

    for(int i = 0; i < l; i++) {
        for(int j = 0; j < w; j++) {
            if(stamp[i][j] != '#') continue;
            if(!out[i][j] && !in[i][j]) return 1e9;

            if(!in[i][j]) {
                int cnt = 1;
                int x = i;
                int y = j;
                while(inrange(x, l) && inrange(y, w) && out[x][y]) {
                    x += dx;
                    y += dy;
                    cnt++;
                }

                ret += (cnt + 1) / 2;
            }
        }
    }

    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int T;
    cin >> T;
    while(T--) {
        int L, W;
        cin >> L >> W;
        vector<P> v;
        vector<vector<char>> stamp(L, vector<char>(W));
        for(int i = 0; i < L; i++) {
            for(int j = 0; j < W; j++) {
                char c;
                cin >> c;
                stamp[i][j] = c;
                if(c == '#') v.emplace_back(i, j);
            }
        }
        sort(v.begin(), v.end());

        int ans = v.size();

        auto cvx = convex_hull(v);
        int n = cvx.size();
        for(int i = 0; i < n; i++) {
            int step_x = cvx[(i+1)%n].x - cvx[i].x;
            int step_y = cvx[(i+1)%n].y - cvx[i].y;
            int g = gcd(step_x, step_y);
            if(g == 0) continue;
            step_x /= g;
            step_y /= g;

            int dx = 0;
            int dy = 0;
            while(true) {
                dx += step_x;
                dy += step_y;

                ans = min(ans, compute(v, stamp, dx, dy));

                if(cvx[(i+1)%n] == P{cvx[i].x + dx, cvx[i].y + dy}) break;
            } 
        }

        cout << ans << "\n";
    }
}