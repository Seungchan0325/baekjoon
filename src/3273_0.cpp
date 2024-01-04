#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_SIZE = 1000000;
int N, X, A[MAX_SIZE];

int main() {
    scanf("%d", &N);
    for(int i=0; i<N; i++)
        scanf("%d", A+i);
    scanf("%d", &X);

    sort(A, A+N);

    int ans=0;
    for(int i=0; i<N; i++) {
        ans += upper_bound(A, A+N, X-A[i]) - lower_bound(A, A+N, X-A[i]);
        while(A[i] == A[i+1]) {
            i++;
            if(i >= N) break;
        }
    }

    printf("%d\n", ans/2);
}