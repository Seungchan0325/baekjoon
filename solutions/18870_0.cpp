#include <iostream>
#include <algorithm>
#include <memory.h>
#include <set>

using namespace std;

const int MAX_N = 1000000;
int N, X[MAX_N], sorted[MAX_N];

int sort_unique(int arr[], int n) {
    sort(arr, arr+N);
    int p = unique(arr, arr+N) - arr;
    for(int i=p; i<N; i++) {
        arr[i] = 0;
    }
    return p;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>N;
    for(int i=0; i<N; i++) {
        cin>>X[i];
        sorted[i] = X[i];
    }

    int size = sort_unique(sorted, N);
    for(int i=0; i<N; i++) {
        int ans = lower_bound(sorted, sorted+size, X[i]) - sorted;
        cout<<ans<<" ";
    }
}