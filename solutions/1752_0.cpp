#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x, y;
    bool operator < (const Point& rhs) const {
        return tie(x, y) < tie(rhs.x, rhs.y);
    }
    bool operator == (const Point& rhs) const {
        return tie(x, y) == tie(rhs.x, rhs.y);
    }
};

int R, C, N;

int main()
{
    cin >> R >> C;
    cin >> N;
    set<Point> s;
    vector<Point> v(N);
    for(auto& [x, y] : v) {
        cin >> x >> y;
    }
    for(int i = 0; i < N; i++) s.insert(v[i]);

    sort(v.begin(), v.end());

    int ans = 0;
    for(int i = 0; i < N; i++) {
        for(int j = i + 1; j < N; j++) {
            int dx = v[j].x - v[i].x;
            int dy = v[j].y - v[i].y;
            Point first = {v[i].x - dx, v[i].y - dy};

            if(first.x < 1 || first.x > R || first.y < 1 || first.y > C) {
                int cnt = 0;
                first.x += dx;
                first.y += dy;
                while(true) {
                    if(first.x < 1 || first.x > R || first.y < 1 || first.y > C) {
                        ans = max(ans, cnt);
                        break;
                    }
                    if(!s.count(first)) break;
                    first.x += dx;
                    first.y += dy;
                    cnt++;
                }
            }
        }
    }

    if(ans <= 2) cout << "0";
    else cout << ans;
}