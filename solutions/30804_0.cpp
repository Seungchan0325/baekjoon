#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

int N, A[MAXN], table[10];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 0; i < N; i++) {
        cin >> A[i];
    }

    int ans = 0;
    int l = 0;
    int r = 0;
    int cnt = 1;
    table[A[0]]++;
    while(r < N) {
        if(cnt > 2) {
            if(--table[A[l++]] == 0) cnt--;
        } else {
            ans = max(ans, r - l + 1);
            if(table[A[++r]]++ == 0) cnt++;
        }
    }

    cout << ans;
}