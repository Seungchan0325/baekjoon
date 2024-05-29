#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;

int n;
unsigned long long v[MAXN];

int main()
{
    cin >> n;
    unsigned long long diff = 0;
    for(int i = 0; i < n; i++) {
        unsigned long long a, b, c, d;
        scanf("%lld.%lld.%lld.%lld", &a, &b, &c, &d);
        v[i] = (a<<24LL) | (b<<16LL) | (c<<8LL) | d;
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            diff |= (v[i] ^ v[j]);
        }
    }

    if(diff == 0) {
        printf("%d.%d.%d.%d\n", (v[0]>>24)&0xFF, (v[0]>>16)&0xFF, (v[0]>>8)&0xFF, v[0]&0xFF);
        printf("255.255.255.255\n");
        return 0;
    }

    unsigned long long mask = ~((1LL<<(32 - __builtin_clz(diff)))-1);
    unsigned long long addr = v[0] & mask;

    printf("%d.%d.%d.%d\n", (addr>>24)&0xFF, (addr>>16)&0xFF, (addr>>8)&0xFF, addr&0xFF);
    printf("%d.%d.%d.%d\n", (mask>>24)&0xFF, (mask>>16)&0xFF, (mask>>8)&0xFF, mask&0xFF);
}