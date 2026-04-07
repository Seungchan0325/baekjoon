#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T, X, N;
    cin >> T >> X;
    cin >> N;
    bool ok = true;
    for(int i = 0; i < N; i++) {
        int k; cin >> k;
        vector<int> v(k);
        for(auto& j : v) cin >> j;
        if(!binary_search(v.begin(), v.end(), X)) ok = false;
    }
    if(ok) cout << "YES\n";
    else cout << "NO\n";
}
