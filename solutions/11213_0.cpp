#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> v(n);
    for(auto& i : v) cin >> i;
    auto vv = v;
    sort(vv.begin(), vv.end(), greater<>());
    int i, j;
    i = j = 0;
    for(;i<n;) {
        j = i;
        while(j < n && vv[i] == vv[j]) j++;
        if(i+1 == j) {
            int idx = find(v.begin(), v.end(), vv[i]) - v.begin() + 1;
            cout << idx << "\n";
            return 0;
        }
        i = j;
    }
    cout << "none\n";
}