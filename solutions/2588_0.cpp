#include <iostream>
#include <string>
using namespace std;
int main() {
	string num, num2;
	cin >> num >> num2;
	for (int i = num2.size()-1; i >= 0; i--) {
		cout << stoi(num) *  (static_cast<char>(num2[i]) - 48)<< endl;
	}
	cout << stoi(num) * stoi(num2);
}