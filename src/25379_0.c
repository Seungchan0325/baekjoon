#include <stdio.h>

#define MIN(x, y) ((x) < (y) ? (x) : (y))

typedef long long int ll;

int readint() {
    register int ret = -1, tmp = -1;
    for(;;) {
        tmp = getchar();
        if(tmp == ' ' || tmp == '\n')
            if(ret == -1) continue;
            else break;

        ret = tmp;
    }
    return ret - '0';
}


ll k[2] = {0, 0}, ans[2] = {0, 0};

int main() {
    int n;
    register int a;

    scanf("%d", &n);
    for(register int i=0; i<n; i++) {
        a = readint() & 1;

        ans[a] += k[a ^ 1];
        k[a]++;
    }

    printf("%lld\n", MIN(ans[0], ans[1]));
}