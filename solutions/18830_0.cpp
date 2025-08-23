#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int dimension = 11;

ll A[1010101];
vector<int> sz(dimension);
vector<int> stride(dimension+1);

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    for(int i = 0; i < dimension; i++) cin >> sz[i];

    int tot = 1;
    stride[dimension] = 1;
    for(int i = dimension-1; i >= 0; i--) {
        tot *= sz[i];
        stride[i] = tot;
    }

    for(int i = 0; i < tot; i++) cin >> A[i];
    
    for(int i = 0; i < dimension; i++) {
        int r = 0;
        for(int j = 0; j < tot; j++) {
            if(j % stride[i] == 0) r = j;
            if(j-stride[i+1] >= r) {
                A[j] += A[j-stride[i+1]];
            }
        }
    }

    int q; cin >> q;
    while(q--) {
        vector<int> is(dimension), js(dimension);
        for(auto& i : is) cin >> i, --i;
        for(auto& j : js) cin >> j, --j;

        ll sum = 0;
        for(int i = 0; i < (1<<dimension); i++) {
            int idx = 0;
            bool inrange = true;
            for(int j = 0; j < dimension; j++) {
                if(i&(1<<j)) idx += js[j] * stride[j+1];
                else {
                    idx += (is[j]-1) * stride[j+1];
                    if(is[j]-1 < 0) inrange = false;
                }
            }
            if(!inrange) continue;
            if(popcount((unsigned)i)&1) sum += A[idx];
            else sum -= A[idx];
        }
        cout << sum << "\n";
    }
}