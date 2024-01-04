#include<iostream>
#include<vector>
#include<math.h>
using namespace std;
bool IsHanNumber(vector<int> N);
vector<int> getVector(int, int);
int main() {
	int N; vector<int> n;
	cin >> N;
	if (N < 100) {
		cout << N;
		return 0;
	}
	if (N == 1000) N = 999;
	int count = 99;
	for (int i = 100; i <= N; i++) {
		n = getVector(i, 3);
		if(IsHanNumber(n)) count++;
	}
	cout << count;
	return 0;
}

vector<int> getVector(int N, int leng) {
	vector<int> placeValue;
	int place;
	while (leng != 0) {
		place = pow(10, leng - 1);
		placeValue.push_back(N / place);
		N -= (N / place)*place;
		leng -= 1;
	}
	return placeValue;
}
bool IsHanNumber(vector<int> N) {
	int size = N.size();
	int d = N[1] - N[0];
	for (int i = 2; i < size; i++) {
		if (N[i] - N[i - 1] != d)
			return false;
	}
	return true;
}