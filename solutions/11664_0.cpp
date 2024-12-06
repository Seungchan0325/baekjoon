#include <bits/stdc++.h>

using namespace std;

struct Vec3 {
    double x, y, z;
    Vec3() : x(0), y(0), z(0) {}
    Vec3(double x, double y, double z) : x(x), y(y), z(z) {}
    Vec3 operator+(const Vec3& rhs) const {
        return Vec3(x + rhs.x, y + rhs.y, z + rhs.z);
    }
    Vec3 operator-(const Vec3& rhs) const {
        return Vec3(x - rhs.x, y - rhs.y, z - rhs.z);
    }
    Vec3 operator*(double rhs) const {
        return Vec3(x * rhs, y * rhs, z * rhs);
    }
    Vec3 operator/(double rhs) const {
        return Vec3(x / rhs, y / rhs, z / rhs);
    }
    double dist(const Vec3& rhs) const {
        return sqrt((x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y) + (z - rhs.z) * (z - rhs.z));
    }
};

Vec3 A, B, C;

int main()
{
    cin >> A.x >> A.y >> A.z >> B.x >> B.y >> B.z >> C.x >> C.y >> C.z;

    Vec3 l = A;
    Vec3 r = B;
    for(int iter = 0; iter < 200; iter++) {
        Vec3 p = (r * 1 + l * 2) / 3;
        Vec3 q = (r * 2 + l * 1) / 3;
        if(p.dist(C) < q.dist(C)) {
            r = q;
        } else {
            l = p;
        }
    }

    cout << fixed << setprecision(10) << l.dist(C) << '\n';
}