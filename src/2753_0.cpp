#include <iostream>
#include <string>
using namespace std;
int main() {
	int year;
	cin >> year;

	cout << ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)));
}