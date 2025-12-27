#include <stdio.h>
#include <vector>
#include "cactus.h"

int main(){
	int N, Q;
	scanf("%d%d", &N, &Q);
	std::vector<int> H(N);
	for(int i = 0; i < N; i++) scanf("%d", &H[i]);
	init(H);
	for(int i = 0; i < Q; i++){
		int S, E;
		scanf("%d%d", &S, &E);
		printf("%lld\n", query(S, E));
	}
	return 0;
}
