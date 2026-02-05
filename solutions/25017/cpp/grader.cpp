#include <cstdio>
#include <vector>

extern long long get_max_score(
	int W, int H,
	std::vector<int> A,
	std::vector<int> X1,
	std::vector<int> Y1,
	std::vector<int> X2,
	std::vector<int> Y2
);

int main() {
	int W, H, N, i;
	scanf("%d%d%d", &W, &H, &N);

	std::vector<int> A(N), X1(N), Y1(N), X2(N), Y2(N);
	for(i = 0; i < N; i++) {
		scanf("%d%d%d%d%d", &A[i], &X1[i], &Y1[i], &X2[i], &Y2[i]);
	}

	const long long ret = get_max_score(W, H, A, X1, Y1, X2, Y2);
	printf("%lld\n", ret);

	return 0;
}
