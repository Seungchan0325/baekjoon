#include <bits/stdc++.h>

using namespace std;

using llint = long long int;

const int MAXN = 500005;

llint N, V[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 0; i < N; i++) {
        cin >> V[i];
    }

    llint pmx = 0, ans = 0;
    for(int i = N-1; i >= 0; i--) {
        pmx = min(V[i], pmx+1);
        ans += pmx;
    }
    cout << ans;
}