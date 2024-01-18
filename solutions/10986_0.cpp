#include <iostream>

using namespace std;

int n, m, zeros;
long long arr[1001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>n>>m;
    long long sum=0, x;
    for(int i=0; i<n; i++) {
        cin>>x;
        sum = (sum + x) % m;
        arr[sum]++;
    }

    long long ans=0;
    for(int i=0; i<m; i++) {
        ans += arr[i] * (arr[i] - 1) / 2;
        //cout<<arr[i]<<" ";
    }
    //cout<<"\n";
    ans+=arr[0];
    cout<<ans<<"\n";
}