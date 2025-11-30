#include <bits/stdc++.h>

using namespace std;

bool sieve[4040404];

int main()
{
    sieve[1] = true;
    for(int i = 2; i < 4040404; i++) {
        if(sieve[i]) continue;
        for(int j = i+i; j < 4040404; j += i) {
            sieve[j] = true;
        }
    }

    int A, B, D;
    cin >> A >> B >> D;
    int cnt = 0;
    for(int i = A; i <= B; i++) {
        if(sieve[i]) continue;
        int n = i;
        while(n) {
            if(n%10 == D) {
                cnt++;
                break;
            }
            n /= 10;
        }
    }
    cout << cnt << "\n";
}