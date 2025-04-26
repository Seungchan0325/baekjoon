#include <bits/stdc++.h>

using namespace std;

int a[101010];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        for(int i = 1; i <= n; i++) cin >> a[i];
        int k = 0;
        vector<int> ans;
        int mx = 0;
        for(int i = 1; i < n; i++) {
            if(max(mx, a[i]) <= i) {
                mx = max(mx, a[i+1]);
                ans.push_back(i);
                k++;
            } else {
                mx = max(mx, a[i]);
            }
        }
        cout << k << "\n";
        for(auto i : ans) cout << i << " ";
        cout << "\n";
    }
}