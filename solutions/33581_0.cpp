#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N, K;
    cin >> N >> K;

    if(N == K) {
        for(int i = N; i >= 1; i--) cout << i << " ";
    } else {
        if(N-1 == K) {
            if(N <= 4) cout << "-1";
            else {
                cout << "1 " << K << " ";
                for(int i = N; i >= 2; i--) {
                    if(i != K && i != N) {
                        cout << i << " ";
                    }
                }
                cout << N << " ";
            }
        } else {
            cout << K+1 << " " << K << " ";
            for(int i = 1; i <= N; i++) {
                if(i != K && i != K+1 && i != K+2) {
                    cout << i << " ";
                }
            }
            cout << K + 2 << " ";
        }
    }
}