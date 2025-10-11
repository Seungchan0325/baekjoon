#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 202020;

int N, A[MAXN];

int main()
{
    int t; cin >> t;
    while(t--) {
        cin >> N;
        for(int i = 1; i <= N; i++) cin >> A[i];
        int diff = 0;
        ll sum = 0;
        for(int i = 1; i <= N; i++) {
            if(A[i] == 0) continue;
            if(A[i] < 0) {
                if(sum <= 0) sum += A[i];
                else {
                    if(sum+A[i] > 0) sum += A[i];
                    else diff += (sum > 0), sum = A[i];
                }
            } else {
                if(sum >= 0) diff += (sum > 0), sum = A[i];
                else {
                    if(sum+A[i] > 0) sum += A[i];
                    else diff -= (sum < 0), sum = A[i];
                }
            }
        }
        if(sum > 0) diff++;
        else if(sum < 0) diff--;

        if(diff > 0) cout << "YES\n";
        else cout << "NO\n";
    }
}