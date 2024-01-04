#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll n;
ll cache[40][40];

ll f(ll w, ll h) {
    if(w == 0 && h == 0) return 1;
    ll& ret = cache[w][h];
    if(ret != -1) return ret;

    ret = 0;
    if(w > 0)
        ret += f(w - 1, h + 1);
    if(h > 0)
        ret += f(w, h - 1);
    
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    while(true) {
        cin >> n;
        if(n == 0) break;

        memset(cache, -1, sizeof(cache));
        ll result = f(n, 0);

        cout << result << "\n";
    }
}