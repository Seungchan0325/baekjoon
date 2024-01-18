#include <iostream>

using namespace std;

using ll = long long;

int n;
ll k[2], ans[2];

int main() {
    scanf("%d", &n);
    int a;
    for(int i=0; i<n; i++) {
        scanf("%d", &a);
        a = a & 1;

        k[a]++;
        ans[!a] += k[!a];
    }

    printf("%ld\n", ans[0] < ans[1] ? ans[0] : ans[1]);
}