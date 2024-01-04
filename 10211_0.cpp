#include <iostream>

using namespace std;

using ll = long long;

int main() {
    int C;
    cin>>C;
    while(C--) {
        int N;
        cin>>N;
        int nums[1000];
        int a;
        cin>>a;
        ll ans=a;
        ll tmp=a;
        for(int i=1; i<N; i++) {
            int a;
            cin>>a;
            tmp = max(tmp + a, (ll)a);
            ans = max(tmp, ans);
        }

        cout<<ans<<endl;
    }
}