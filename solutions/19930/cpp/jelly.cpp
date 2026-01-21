#ifdef LSC_ENV
#include "grader.cpp"
#endif

#include "jelly.h"
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2020;
const int MAXX = 10101;
const int inf = 1e9;

int N, DP[MAXN][MAXX], R[MAXN][MAXX], A[MAXN], B[MAXN];

// DP[i][j] = [1, i]에서 A에 j원 이하로 사용할 때 B에 사용하는 최소 비용
// R[i][j] = [i, N]에서 B에 j원 이하로 얻을 수 있는 최대 개수

int find_maximum_unique(int x, int y, vector<int> a, vector<int> b) {
	N = a.size();
	vector<pair<int, int>> ab;
	for(int i = 0; i < N; i++) {
		ab.emplace_back(a[i], b[i]);
	}
	sort(ab.begin(), ab.end());
	for(int i = 0; i < N; i++) {
		A[i+1] = ab[i].first;
		B[i+1] = ab[i].second;
	}

	for(int i = 1; i <= N; i++) {
		for(int j = 0; j <= x; j++) {
			DP[i][j] = DP[i-1][j] + B[i];
			if(j > 0) DP[i][j] = min(DP[i][j-1], DP[i][j]);
			if(j >= A[i]) DP[i][j] = min(DP[i][j], DP[i-1][j-A[i]]);
		}
	}
	for(int i = N; i >= 1; i--) {
		for(int j = 0; j <= y; j++) {
			R[i][j] = R[i+1][j];
			if(j > 0) R[i][j] = max(R[i][j], R[i][j-1]);
			if(j >= B[i]) R[i][j] = max(R[i][j], R[i+1][j-B[i]] + 1);
		}
	}

	int ans = 0;
	for(int i = 0; i <= N; i++) {
		if(DP[i][x] <= y) {
			ans = max(ans, i + R[i+1][y-DP[i][x]]);
		}
	}
	return ans;
}
