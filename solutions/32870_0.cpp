#include <bits/stdc++.h>

using namespace std;

const int MAXN = 303030;

int N, Q, A[MAXN], mn[MAXN], mx[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    memset(mn, -1, sizeof(mn));

    cin >> N >> Q;
    for(int i = 1; i <= N; i++) {
        cin >> A[i];
    }
    sort(A+1, A+N+1);

    A[0] = -1e9;
    A[N+1] = 1e9;
    while(Q--) {
        int m;
        cin >> m;
        if(mn[m] == -1) {
            mn[m] = 1e9;
            mx[m] = -1;
            int j = 1;
            for(int i = 0; j <= N; i+=m) {
                j = lower_bound(A+j, A+N+1, i) - A;
                mn[m] = min(mn[m], A[j] - i);
                mx[m] = max(mx[m], A[j-1] - i + m);
            }
        }
        cout << mn[m] << " " << mx[m] << "\n";
    }
}