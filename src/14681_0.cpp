#include <iostream>
#include <string>
using namespace std;
inline int is_minuse(int x) { return x < 0; }
int main() {
	int x, y;
	cin >> x >> y;


	int output;
	if (is_minuse(x)) {
		if (is_minuse(y)) {
			output = 3;
		}
		else {
			output = 2;
		}
	}
	else {
		if (is_minuse(y)) {
			output = 4;
		}
		else {
			output = 1;
		}
	}

	cout << output;
}