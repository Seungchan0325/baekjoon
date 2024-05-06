#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 5;

int N, A[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 0; i < N; i++) cin >> A[i];
    
    int ans = 0;
    for(int i = 0; i < N; i++) {
        if(A[i+1] > A[i+2]) {
            int d = min(A[i], A[i+1] - A[i+2]);
            ans += d * 5;
            A[i] -= d; A[i+1] -= d;

            d = min({A[i], A[i+1], A[i+2]});
            ans += d * 7;
            A[i] -= d; A[i+1] -= d; A[i+2] -= d;
        } else {
            int d = min({A[i], A[i+1], A[i+2]});
            ans += d * 7;
            A[i] -= d; A[i+1] -= d; A[i+2] -= d;

            d = min(A[i], A[i+1]);
            ans += d * 5;
            A[i] -= d; A[i+1] -= d;
        }
        ans += A[i] * 3;
    }

    cout << ans;
}