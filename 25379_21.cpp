#include <stdio.h>

#define MIN(x, y) ((x) < (y) ? (x) : (y))

typedef long long int ll;

int main() {
    int n, a;
    ll k1, k2, ans1, ans2;
    k1 = k2 = ans1 = ans2 = 0;

    scanf("%d", &n);
    for(register int i=0; i<n; i++) {
        scanf("%d", &a);
        if(a & 1) {
            k1++;
            ans2 += k2;
        } else {
            k2++;
            ans1 += k1;
        }
    }

    printf("%lld\n", MIN(ans1, ans2));
}