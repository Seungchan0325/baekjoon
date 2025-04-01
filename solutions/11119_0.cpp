#include <bits/stdc++.h>

using namespace std;
double ccw(double x1, double y1, double x2, double y2, double x3, double y3)
{
    double ret = (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);
    if(abs(ret) <= DBL_EPSILON) return 0;
    if(ret < 0) return -1;
    if(ret > 0) return 1;
    assert(0);
}
bool isin(tuple<double, double, double> cir, double x, double y)
{
    auto [a, b, r] = cir;
    return (x - a) * (x - a) + (y - b) * (y - b) <= r*r;
}
bool isin(tuple<double, double, double, double> rect, double x, double y)
{
    auto [x1, y1, x2, y2] = rect;
    return x1 <= x && x <= x2 && y1 <= y && y <= y2;
}
bool isin(tuple<double, double, double, double, double, double> tri, double x, double y)
{
    auto [x1, y1, x2, y2, x3, y3] = tri;
    return ccw(x1, y1, x2, y2, x3, y3) * ccw(x1, y1, x2, y2, x, y) >= 0 &&
           ccw(x2, y2, x3, y3, x1, y1) * ccw(x2, y2, x3, y3, x, y) >= 0 &&
           ccw(x3, y3, x1, y1, x2, y2) * ccw(x3, y3, x1, y1, x, y) >= 0;
}
vector<tuple<double, double, double>> cir;
vector<tuple<double, double, double, double>> rect;
vector<tuple<double, double, double, double, double, double>> tri;
int count(double x, double y)
{
    int ret = 0;
    for(auto c : cir) ret += isin(c, x, y);
    for(auto r : rect) ret += isin(r, x, y);
    for(auto t : tri) ret += isin(t, x, y);
    return ret;
}
int main()
{
    int s;
    cin >> s;
    for(int i = 0; i < s; i++) {
        char shape; cin >> shape;
        if(shape == 'C') {
            double x, y, r;
            cin >> x >> y >> r;
            cir.emplace_back(x, y, r);
        } else if(shape == 'R') {
            double x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            rect.emplace_back(x1, y1, x2, y2);
        } else if(shape == 'T') {
            double x1, y1, x2, y2, x3, y3;
            cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
            tri.emplace_back(x1, y1, x2 ,y2, x3, y3);
        }
    }
    int n;
    cin >> n;
    while(n--) {
        int c1 = 0;
        for(int i = 0; i < 3; i++) {
            double x, y;
            cin >> x >> y;
            c1 += count(x, y);
        }
        int c2 = 0;
        for(int i = 0; i < 3; i++) {
            double x, y;
            cin >> x >> y;
            c2 += count(x, y);
        }
        if(c1 == c2) cout << "Tied\n";
        if(c1 > c2) cout << "Bob\n";
        if(c1 < c2) cout << "Hannah\n";
    }
}