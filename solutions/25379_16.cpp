#include <stdio.h>

#define MIN(x, y) ((x) < (y) ? (x) : (y))

typedef long long int ll;

int readint() {
    int ret = -1, tmp = -1;
    while(1) {
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
    int n, a;

    scanf("%d", &n);
    for(int i=0; i<n; i++) {
        a = readint();
        a = a & 1;

        k[a]++;
        ans[a] += k[a ^ 1];
    }

    printf("%lld\n", MIN(ans[0], ans[1]));
}