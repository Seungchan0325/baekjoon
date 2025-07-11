#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 505050;

int N;
ll A[3][MAXN], s;

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[1][i], A[1][i] += A[1][i-1];
    for(int i = 1; i <= N; i++) cin >> A[2][i], A[2][i] += A[2][i-1];

    ll otto = -1;
    ll dave = -1;

    s = A[1][N] + A[2][N];
    
    if(~N&1) {
        auto update = [&](ll option) {
            if(dave < option) {
                otto = s - option;
                dave = option;
            }
        };
        update(s-A[1][N/2+1]-A[2][N/2+1]);
        update(min(A[2][N], s-A[1][N/2]-A[2][N/2]));
    } else {
        auto update = [&](ll option) {
            if(otto < option) {
                otto = option;
                dave = s - option;
            }
        };
        update(A[1][N/2]+A[2][N/2]);
        update(min(A[1][N], A[1][N/2+1]+A[2][N/2+1]));
    }

    cout << otto << " " << dave << "\n";
}