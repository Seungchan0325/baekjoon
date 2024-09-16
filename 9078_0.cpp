#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;

int T, N, A[MAXN];

int main()
{
    cin >> T;
    while(T--) {
        cin >> N;
        for(int i = 1; i <= N; i++) {
            cin >> A[i];
        }

        int inv = 0;
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j < i; j++) {
                if(A[j] > A[i]) {
                    inv++;
                }
            }
        }

        if(~inv & 1) cout << "YES\n";
        else cout << "NO\n";
    }
}