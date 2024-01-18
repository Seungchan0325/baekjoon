#include <bits/stdc++.h>

using namespace std;

using ll = long long;

bool check[1000500];
ll mmin, mmax;

int main() {
    cin >> mmin >> mmax;

    ll cnt = mmax - mmin + 1;
    for(ll i = 2; i*i <= mmax; i++) {
        ll start = mmin / (i*i);
        if(start * i*i < mmin) start++;
        start *= i*i;

        while(start <= mmax) {
            if(!check[start - mmin]) {
                check[start - mmin] = true;
                cnt--;
            }
            start += i*i;
        }
    }

    cout << cnt;
}