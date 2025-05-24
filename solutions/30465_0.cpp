#include <bits/stdc++.h>

using namespace std;

const int MAXN = 202020;

int n, a[MAXN];
vector<vector<int>> cycs;

void decomp()
{
    vector<bool> vst(n+1);
    for(int i = 1; i <= n; i++) {
        if(vst[i]) continue;
        vector<int> cyc;
        int j = i;
        while(!vst[j]) {
            vst[j] = true;
            cyc.push_back(j);
            j = a[j];
        }
        cycs.push_back(cyc);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    
    if((n&1) && a[(n+1)/2] != (n+1)/2) {
        cout << "-1\n";
        return 0;
    }
    

    decomp();

    int l, r;
    l = r = 0;
    for(auto cyc : cycs) {
        if(cyc.size() == 1) continue;
        int mn = *min_element(cyc.begin(), cyc.end());
        int mx = *max_element(cyc.begin(), cyc.end());
        if(mx <= n/2) l++;
        if(mn > n/2) r++;
    }
    int ans = 2 * max(l, r) + n - ssize(cycs);
    cout << ans << "\n";
}