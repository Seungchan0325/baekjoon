#include <iostream>

using namespace std;

int n;
char arr[1000000];

int main() {
    scanf("%d", &n);
    for(int i=0; i<n; i++) {
        int a; scanf("%d", &a);
        arr[i] = a & 1;
    }

    int k[2] = {0, 0}, ans[2] = {0, 0};
    for(int i=0; i<n; i++) {
        k[arr[i]]++;
        ans[!arr[i]] += k[!arr[i]];
    }

    printf("%d\n", ans[0] < ans[1] ? ans[0] : ans[1]);
}