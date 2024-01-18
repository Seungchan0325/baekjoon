#include <iostream>
#include <string>
using namespace std;
int main() {
	int score;
	cin >> score;
	if (score == 100)score = 90;
	score -= (score % 10);

	char output;
	switch (score) {
	case 90:
		output = 'A';
		break;
	case 80:
		output = 'B';
		break;
	case 70:
		output = 'C';
		break;
	case 60:
		output = 'D';
		break;
	default:
		output = 'F';
		break;
	}
	cout << output;
}