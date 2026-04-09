#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main()
{
    ll N, M, X;
    cin >> N >> M >> X;
    for(ll n = 1; n <= N; n++) {
        if(X % n == 0 && X/n <= M) {
            cout << "1\n";
            cout << "0 0 " << n << " " << X / n << "\n";
            return 0;
        }
    }

    cout << "2\n";
    cout << "0 0 " << N << " " << X/N << "\n";
    cout << "0 " << X/N << " " << X%N << " " << X/N+1 << "\n";
}
