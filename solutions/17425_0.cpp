#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 1000005;

ll psum[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    for(int i = 1; i < MAXN; i++) {
        for(int j = i; j < MAXN; j += i) {
            psum[j] += i;
        }
    }

    for(int i = 1; i < MAXN; i++) {
        psum[i] += psum[i-1];
    }

    int tc;
    cin >> tc;
    while(tc--) {
        int n;
        cin >> n;
        cout << psum[n] << "\n";
    }
}