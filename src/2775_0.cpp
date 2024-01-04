#include <iostream>
#include <vector>

using namespace std;

int getSum(int arr[][15], int currentRow, int currentCol) {
	
	int sum = 0;

	for (int i = 1; i <= currentCol; i++)
		sum += arr[currentRow - 1][i];

	return sum;
}

int main(void) {

	int testCase;
	int k, n;
	vector<int> arr;
	int location[15][15];

	for (int i = 1; i <= 14; i++)
		location[0][i] = i;
	for (int i = 1; i <= 14; i++) {
		for (int j = 1; j <= 14; j++) {
			location[i][j] = getSum(location, i, j);
		}
	}

	cin >> testCase;
	for (int i = 0; i < testCase; i++) {
		
		cin >> k;
		cin >> n;
		arr.push_back(location[k][n]);
	}

	for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << endl;

	return 0;
}