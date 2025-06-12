#include <bits/stdc++.h>

using namespace std;

struct Ln {
    int l, r, w;
};

const int MAXN = 1010;

int n, K, sum, h[MAXN], dp[1010101][30];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> K;
    vector<int> v;
    v.push_back(0);
    for(int i = 1; i <= n; i++) {
        cin >> h[i];
        sum += h[i];
        v.push_back(h[i]);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    
    for(int i = 1; i <= n; i++) {
        h[i] = lower_bound(v.begin(), v.end(), h[i]) - v.begin();
    }

    vector<Ln> ln;
    for(int i = 1; i <= n; i++) {
        int k = i-1;
        for(int j = h[i]; j > h[i-1]; j--) {
            while(k < n && h[k+1] >= j) k++;
            if(ln.size() && ln.back().l == i && ln.back().r == k)
                ln.back().w += (k - i + 1) * (v[j] - v[j-1]);
            else
                ln.push_back({i, k, (k - i + 1) * (v[j] - v[j-1])});
        }
    }

    assert(ln.size() <= 1010101);

    sort(ln.begin(), ln.end(), [](Ln a, Ln b){
        if(a.l != b.l) return a.l < b.l;
        return a.r > b.r;
    });

    int ans = 1e9+7;
    for(int i = 0; i < ln.size(); i++) {
        for(int j = 1; j <= K; j++) {
            dp[i][j] = ln[i].w;
            for(int k = 0; k < i; k++) {
                if(ln[k].r >= ln[i].r) {
                    dp[i][j] = max(dp[i][j], dp[k][j] + ln[i].w);
                } else {
                    dp[i][j] = max(dp[i][j], dp[k][j-1] + ln[i].w);
                }
            }
            ans = min(ans, sum - dp[i][j]);
        }
    }

    cout << ans;
}