#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    int a[10001], d[10001];
    
    scanf("%d", &n);
    for(int i=1; i<=n; i++)
        scanf("%d", a+i);
    
    d[1] = a[1];
    d[2] = d[1] + a[2];
    for(int i=3; i<=n; i++) {
        d[i] = max({d[i-3] + a[i-1] + a[i], d[i-1], d[i-2] + a[i]});
    }
    printf("%d", d[n]);
}