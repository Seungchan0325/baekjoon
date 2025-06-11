#include <bits/stdc++.h>

using namespace std;

const int MAXN = 303030;
const int LOGN = 20;

int n, m, s[MAXN], e[MAXN], sparse[MAXN][LOGN+1];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> m;
    s[n+1] = e[n+1] = -1;
    s[n+2] = e[n+2] = 1e9 + 7;
    for(int i = 1; i <= n; i++) {
        cin >> s[i] >> e[i];
    }
    vector<int> v(n+2); iota(v.begin(), v.end(), 1);
    sort(v.begin(), v.end(), [](int i, int j){
        if(e[i] != e[j]) return e[i] < e[j];
        return s[i] < s[j];
    });

    priority_queue<pair<int, int>> pq;
    for(int i : v) {
        while(pq.size() && -pq.top().first < s[i]) {
            sparse[pq.top().second][0] = i;
            pq.pop();
        }
        pq.emplace(-e[i], i);
    }

    for(int i = 1; i <= LOGN; i++) {
        for(int j = 1; j <= n+2; j++) {
            sparse[j][i] = sparse[sparse[j][i-1]][i-1];
        }
    }

    while(m--) {
        int k;
        cin >> k;
        vector<int> p(k);
        for(auto& i : p) cin >> i;
        p.push_back(n+2);

        int cnt = 0;
        int idx = n+1;
        for(auto j : p) {
            for(int i = LOGN; i >= 0; i--) {
                if(sparse[idx][i] != 0 && e[sparse[idx][i]] < s[j]) {
                    cnt += 1<<i;
                    idx = sparse[idx][i];
                }
            }
            idx = j;
        }
        cout << cnt + k << "\n";
    }
}