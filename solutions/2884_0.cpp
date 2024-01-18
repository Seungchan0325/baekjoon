#include <iostream>
#include <string>
using namespace std;
inline int is_minuse(int x) { return x < 0; }
int main() {
	int h, m;
	cin >> h >> m;

	if (is_minuse(m - 45)) {
		if (h == 0) {
			h = 24;
		}
		h--;
		m = m+60 - 45;
	}
	else {
		m -= 45;
	}
	cout << h << ' ' << m;
}