#include <iostream>

using namespace std;

int n;
bool arr[1000000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>n;
    for(int i=0; i<n; i++) {
        int a;
        cin>>a;
        arr[i] = a & 1 ? 0 : 1;
    }

    int ans[2] = {0, 0};
    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            if(arr[i] != arr[j]) ans[arr[i]]++;
        }
    }

    cout<<min(ans[0], ans[1])<<"\n";
}