#include <bits/stdc++.h>

using namespace std;

const int MAXK = 1010101;

int n, k, s[2*MAXK], e[2*MAXK], sparse[2*MAXK][22];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> k;
    for(int i = 1; i <= k; i++) {
        cin >> s[i] >> e[i]; s[i]--, e[i]--;
        if(e[i] < s[i]) e[i] += n;
        s[i+k] = s[i]+n;
        e[i+k] = e[i]+n;
    }
    vector<int> sv(2*k), ev(2*k);
    iota(sv.begin(), sv.end(), 1);
    iota(ev.begin(), ev.end(), 1);
    sort(sv.begin(), sv.end(), [](int i, int j) {
        return s[i] < s[j];
    });
    sort(ev.begin(), ev.end(), [](int i, int j) {
        return e[i] < e[j];
    });

    int j = 0;
    priority_queue<pair<int, int>> pq;
    for(auto i : ev) {
        while(j < sv.size() && s[sv[j]] <= e[i]+1) {
            pq.emplace(e[sv[j]], sv[j]);
            j++;
        }
        if(pq.size()) {
            sparse[i][0] = pq.top().second;
        }
    }

    for(int i = 1; i < 22; i++)
        for(int j = 1; j <= 2*k; j++)
            sparse[j][i] = sparse[sparse[j][i-1]][i-1];

    int ans = 1e9;
    for(int i = 1; i <= 2*k; i++) {
        int j = i;
        int cnt = 1;
        for(int k = 21; k >= 0; k--) {
            if(sparse[j][k] && e[sparse[j][k]] < s[i]+n-1) {
                cnt += (1<<k);
                j = sparse[j][k];
            }
        }
        if(sparse[j][0] && e[sparse[j][0]] >= s[i]+n-1)
            ans = min(ans, cnt+1);
        if(e[j] >= s[i]+n-1) ans = min(ans, cnt);
    }

    if(ans >= 1e9) cout << "impossible\n";
    else cout << ans << "\n";
}