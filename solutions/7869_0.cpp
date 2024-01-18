#include <bits/stdc++.h>

using namespace std;

const double PI = M_PI;

double _x1, _y1, _r1;
double _x2, _y2, _r2;

int main()
{
    cin >> _x1 >> _y1 >> _r1 >> _x2 >> _y2 >> _r2;

    double d = hypot(abs(_x1 - _x2), abs(_y1 - _y2));

    if(_r1 < _r2) swap(_r1, _r2);

    double area = -1;
    if(_r1 + _r2 < d)
    {
        area = 0;
    }
    else if(d < 1e-5 || d + _r2 < _r1)
    {
        area = PI * _r2 * _r2;
    }
    else
    {
        double x = (_r1 * _r1 - _r2 * _r2 + d * d) / (2 * d);
        double y = sqrt(_r1 * _r1 - x * x);

        double theta1 = acos(x / _r1);
        double theta2 = acos((d - x) / _r2);

        double tri1 = x * y;
        double tri2 = (d - x) * y;

        double arc1 = _r1 * _r1 * PI * 2 * theta1 / (2 * PI);
        double arc2 = _r2 * _r2 * PI * 2 * theta2 / (2 * PI);
        
        area = arc1 + arc2 - tri1 - tri2;
    }

    printf("%.3f\n", area);
}