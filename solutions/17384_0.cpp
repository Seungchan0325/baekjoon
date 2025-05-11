#include <bits/stdc++.h>

using namespace std;

int N, M, A[2000000];

int main()
{
    cin >> N;
    M = bit_ceil((unsigned)N);
    int diff = M - N;
    int x = M;
    for(int i = 22; i >= 0; i--) {
        if(diff&(1<<i)) {
            for(int j = 0; j < (1<<i); j++) {
                A[x-j] = 1;
            }
            x -= 1<<i;
            x -= 1<<i;
        }
    }
    for(int i = 1; i <= M; i++) {
        if(A[i]) cout << ".";
        else cout << "#";
    }
}