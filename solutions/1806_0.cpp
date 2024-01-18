#include <iostream>
#include <vector>
#include <limits>

using namespace std;

using ll = long long;

ll n, s;
vector<ll> prefix_sum;

int main() {
    cin >> n >> s;
    prefix_sum.resize(n+1, 0);
    for(int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        prefix_sum[i] = prefix_sum[i-1] + a;
    }

    int len = INT32_MAX;
    int l = 0, r = 0;
    while(l <= n && r <= n) {
        auto sum = prefix_sum[r] - prefix_sum[l];
        if(sum >= s) {
            len = min(len, r-l);
            l++;
        } else {
            r++;
        }
    }

    if (len == INT32_MAX) {
        len = 0;
    }

    cout << len;
}