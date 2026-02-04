#pragma GCC optimize("O3", "Ofast", "unroll-loop")
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50505;

int N, M;
int H[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    while(M--) {
        int t;
        cin >> t;
        if(t == 1) {
            int D;
            cin >> D;
            int l = 0;
            int r = 0;
            for(int i = 1; i <= N; i++) {
                l = H[i] ? 0 : l+1;
                if(l == D) {
                    r = i - D + 1;
                    break;
                }
            }
            cout << r << "\n";
            if(r) {
                for(int i = 0; i < D; i++) H[r+i] = 1;
            }
        } else {
            int X, D;
            cin >> X >> D;
            for(int i = 0; i < D; i++) {
                H[i+X] = 0;
            }
        }
    }
}