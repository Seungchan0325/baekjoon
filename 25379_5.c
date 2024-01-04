#include <stdio.h>

#define MIN(x, y) ((x) < (y) ? (x) : (y))

typedef long long int ll;

int main() {
    int n, a;
    ll k[2] = {0, 0}, ans[2] = {0, 0};

    scanf("%d", &n);
    for(register int i=0; i<n; i++) {
        scanf("%d", &a);
        a = a & 1;

        k[a]++;
        ans[!a] += k[!a];
    }

    printf("%lld\n", MIN(ans[0], ans[1]));
}