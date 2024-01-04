#include <bits/stdc++.h>

using namespace std;

struct vector2
{
	double x, y;
    vector2() : x(0), y(0) {}
    vector2(double x_, double y_) : x(x_), y(y_) {}
	bool operator == (const vector2& rhs) const {
		return (x == rhs.x && y == rhs.y);
	}
	bool operator < (const vector2& rhs) const {
		return (x != rhs.x ? x < rhs.x : y < rhs.y);
	}
	vector2 operator + (const vector2& rhs) const {
		return vector2(x + rhs.x, y + rhs.y);
	}
	vector2 operator - (const vector2& rhs) const {
		return vector2(x - rhs.x, y - rhs.y);
	}
	vector2 operator * (double rhs) const {
		return vector2(x*rhs, y*rhs);
	}

	double norm() const{ return hypot(x,y); }
};

int n;
vector<vector2> vs;

double GetMinVectorSum(int idx, int selected, vector2 sum) {
    if(idx == n) {
        if(selected == n / 2)
            return sum.norm();

        return numeric_limits<double>::infinity();
    }

    double ret = INFINITY;
    ret = min(ret, GetMinVectorSum(idx + 1, selected + 1, sum + vs[idx]));
    ret = min(ret, GetMinVectorSum(idx + 1, selected, sum - vs[idx]));

    return ret;
}

int main() {
    int t; cin >> t;
    while(t--) {
        cin >> n;
        vs = vector<vector2>(n);
        for(auto& i : vs)
            cin >> i.x >> i.y;

        double result = GetMinVectorSum(0, 0, vector2());
        cout << setprecision(10) << result << "\n";
        //cout << format("{:.6f}\n", result);
    }
}