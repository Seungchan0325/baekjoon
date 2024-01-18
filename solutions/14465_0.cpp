#include <iostream>
#include <numeric>

using namespace std;

#define INF 987654321
#define MAX_N 100000

int N, B, K, arr[MAX_N];

int main() {
    cin>>N>>K>>B;
    for(int i=0; i<B; i++) {
        int a;
        cin>>a;
        arr[a-1] = true;
    }

    int ans = INF;
    for(int i=0; i<N-K+1; i++) {
        ans = min(accumulate(arr+i, arr+i+K, 0), ans);
    }
    cout<<ans<<endl;
}