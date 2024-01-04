#include <iostream>
#include <algorithm>

using namespace std;

using ll = long long;

#define MAX_N 100000

int N, K, nums[MAX_N];
ll _prefix_sum[MAX_N+1];

ll prefix_sum(int i, int j) {
    return _prefix_sum[j] - _prefix_sum[i-1];
}

int main() {
    scanf("%d", &N);
    for(int i=0; i<N; i++)
        scanf("%d", nums + i);
    scanf("%d", &K);

    for(int i=1; i<=N; i++) {
        _prefix_sum[i] = _prefix_sum[i-1] + (ll)nums[i-1];
    }

    ll cnt=0;
    for(int i=1; i<=N; i++) {
        int j=i;
        while(prefix_sum(i, j) <= (ll)K && j <= N) j++;
        cnt += N - j + 1;
    }
    cout<<cnt<<endl;
}