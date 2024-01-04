#include <iostream>

using namespace std;

int n, arr[1000000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>n;
    for(int i=0; i<n; i++) {
        int a;
        cin>>a;
        arr[i] = a & 1;
    }

    int k[2] = {0, 0}, ans[2] = {0, 0};
    for(int i=0; i<n; i++) {
        k[arr[i]]++;
        ans[!arr[i]] += k[!arr[i]];
    }

    cout<<min(ans[0], ans[1])<<"\n";
}