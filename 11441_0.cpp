#include <stdio.h>

typedef long long ll;

int i, j, N, M, A[100000];
ll prefix_sum[100001];

int main(void)
{
    scanf("%d", &N);
    for(i=0; i<N; i++)
        scanf("%d", A + i);
    scanf("%d", &M);

    for(i=1; i<=N; i++)
        prefix_sum[i] = prefix_sum[i-1] + A[i-1];
    

    while(M--) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d\n", prefix_sum[b] - prefix_sum[a-1]);
    }
}