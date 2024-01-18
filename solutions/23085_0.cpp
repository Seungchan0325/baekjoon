#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3005;

int n, k;
bool visited[MAXN];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> k;
    string s; cin >> s;

    int ans = -1;
    int init_h = count(s.begin(), s.end(), 'H');
    queue<pair<int, int>> q;

    q.push({init_h, 0});
    visited[init_h] = true;

    while(!q.empty()) {
        auto [H, step] = q.front(); q.pop();
        int T = n - H;

        if(!H) {
            ans = step;
            break;
        }

        for(int i = 0; i <= min(k, H); i++) {
            int in = k - i;
            int out = i;

            int nT = T + out - in;
            int nH = H + in - out;
            if(T < in || H < out) continue;
            if(nH < 0 || n < nH || nT < 0 || n < nT || visited[nH]) continue;
            q.push({nH, step+1});
            visited[nH] = true;
        }
    }

    cout << ans;
}