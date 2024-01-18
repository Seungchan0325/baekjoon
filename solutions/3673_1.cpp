//S(i) = i 번째 prefix sum
//(S(i) - S(j)) % d = 0를 카운트
//(S(i)) - S(j)) % d = S(i) % d - S(j) % d = 0
//따라서 S(i) % d = S(j) % d 이를 카운트

#include <iostream>
#include <memory.h>

using namespace std;

int c, d, n;
long long a, sum, S[1000000];

int main() {
    cin>>c;
    while(c--) {
        memset(S, 0, sizeof(S));
        cin>>d>>n;
        sum = 0;
        for(int i=0; i<n; i++) {
            cin>>a;
            sum = (sum + (a % d)) % d;
            S[sum]++;
        }

        long long ans = 0;
        ans += S[0];
        for(int i=0; i<d; i++) {
            ans += S[i] * (S[i] - 1) / 2;
        }
        cout<<ans<<"\n";
    }
}