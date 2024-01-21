#include <bits/stdc++.h>

using namespace std;

int main()
{
    double r, h, d1, a1, d2, a2;
    while(cin >> r >> h >> d1 >> a1 >> d2 >> a2) {
        double ratio = r / sqrt(h * h + r * r);
        double theta = min(abs(a1 - a2), 360.0 - abs(a1 - a2)) * ratio * M_PI / 180.0;
        double dx = abs(d2 * cos(theta) - d1);
        double dy = abs(d2 * sin(theta));
        double ans = sqrt(dx * dx + dy * dy);
        printf("%0.2f\n", ans);
    }
}