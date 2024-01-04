#include <stdio.h>

int main() {
    int n; scanf("%d", &n);

    long long p1 = 1, p2 = 1;

    for(int i=1; i<n; i++) {
        long long tmp = p1 + p2;
        p1 = p2;
        p2 = tmp;
    }

    printf("%lld\n", p1);

    return 0;
}