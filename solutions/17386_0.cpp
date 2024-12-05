#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Point {
    ll x, y;
};

ll ccw(Point p1, Point p2, Point p3)
{
    ll ret = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
    if(ret < 0) return -1;
    if(ret > 0) return 1;
    return 0;
}

int main()
{
    Point p1, p2, p3, p4;
    cin >> p1.x >> p1.y >> p2.x >> p2.y;
    cin >> p3.x >> p3.y >> p4.x >> p4.y;

    if(ccw(p1, p2, p3) * ccw(p1, p2, p4) < 0 && ccw(p3, p4, p1) * ccw(p3, p4, p2) < 0) cout << "1";
    else cout << "0";
}