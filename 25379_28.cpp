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

    int ans1 = 0;
    int ans2 = 0;
    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            if(arr[i] < arr[j]) {
                ans1++;
            } else if(arr[j] < arr[i]) {
                ans2++;
            }
        }
    }

    cout<<min(ans1, ans2)<<"\n";
}