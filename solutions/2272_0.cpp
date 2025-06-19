#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010101;

int n, m;
bitset<MAXN> on;

int main()
{
    cin >> n >> m;
    for(int i = n-1; i >= 0; i--) {
        int x; cin >> x;
        if(x) on.set(i);
    }
    for(long long k = 1; k < (1LL<<31); k<<=1) {
        if(m&k) {
            auto tmp = on;
            for(int i = 0; i < n; i++) {
                if(tmp.test(i))
                    on.flip((i+k)%n);
            }
        }
    }
    for(int i = n-1; i >= 0; i--) {
        if(on.test(i)) cout << "1\n";
        else cout << "0\n";
    }
}