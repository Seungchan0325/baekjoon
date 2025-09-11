#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

int N, K;
char A[MAXN], B[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;
    for(int i = 0; i < N; i++) {
        char c; cin >> c;
        if(c == 'R') A[i] = 1;
        else if(c == 'G') A[i] = 2;
        else A[i] = 0;
    }

    int gap = 1;
    while(K) {
        for(int i = 0; i < K%3; i++) {
            for(int j = 0; j < N; j++) B[j] = (A[j]+A[(j+gap)%N]+A[((j-gap)+N)%N])%3;
            for(int j = 0; j < N; j++) A[j] = B[j];
        }
        gap *= 3;
        gap %= N;
        K /= 3;
    }

    int cnt[3] = {};
    for(int i = 0; i < N; i++) {
        cnt[A[i]]++;
    }
    cout << cnt[1] << " " << cnt[2] << " " << cnt[0] << "\n";
}