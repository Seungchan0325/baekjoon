#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 505050;

int N, L[MAXN];

int main()
{
    cin >> N;
    for(int i = 0; i < N; i++) cin >> L[i];
    sort(L, L+N);
    ll s = 0;
    int i;
    for(i = 0; i < N; i++) {
        if(s+L[i] <= N-i-2) s+=L[i];
        else break;
    }
    if(s < N-i-1) cout << N-i-1;
    else cout << s;
}