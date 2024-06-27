#include <bits/stdc++.h>

using namespace std;

int main()
{
    int x1, y1, x2, y2, x3, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    int ccw = x1 * y2 + x2 * y3 + x3 * y1 - y1 * x2 - y2 * x3 - y3 * x1;
    if(ccw < 0) puts("-1");
    else if(ccw > 0) puts("1");
    else puts("0");
}