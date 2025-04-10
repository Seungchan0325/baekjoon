#include <bits/stdc++.h>

using namespace std;

int main()
{
    int k, n;
    cin >> k >> n;
    vector<string> v(k);
    for(auto& i : v) cin >> i;
    sort(v.begin(), v.end(), [](string& a, string& b){
        // if(a.size() != b.size()) return a.size() > b.size();
        return a + b > b + a;
    });
    int mxi = -1;
    for(int i = 0; i < k; i++) {
        if(v[mxi].size() < v[i].size()) mxi = i;
    }
    int j = 0;
    for(int i = 0; i < n; i++) {
        cout << v[j];
        if(j < k && (n - i <= k - j || j < mxi)) j++;
    }
}