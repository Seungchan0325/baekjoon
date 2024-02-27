#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD = 1e9 + 7;

const int MAXN = 1000005;

int N, Q;
ll arr[MAXN], fibo[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;

    fibo[0] = 0;
    fibo[1] = 1;
    for(int i = 2; i <= MAXN; i++) {
        fibo[i] = (fibo[i-1] + fibo[i-2]) % MOD;
    }

    cin >> Q;
    while(Q--) {
        int l, r;
        cin >> l >> r;

        arr[l] = (arr[l] + 1) % MOD;
        arr[r+2] = (arr[r+2] + MOD - fibo[r-l+1]) % MOD;
        arr[r+1] = (arr[r+1] + MOD - fibo[r-l+2]) % MOD;
    }

    for(int i = 2; i <= N; i++) {
        arr[i] = (arr[i] + arr[i-1] + arr[i-2] + MOD) % MOD;
    }

    for(int i = 1; i <= N; i++) {
        cout << arr[i] << " ";
    }
}