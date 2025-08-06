#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353;

struct Rect {
    int x1, y1, x2, y2;
};

int N;

int solve(vector<pair<int, int>> lr)
{
    sort(lr.begin(), lr.end());
    int ans = 0;
    int cnt = 0;
    int sum = 0;
    priority_queue<int, vector<int>, greater<>> pq;
    for(int i = 0; i < N; i++) {
        while(pq.size() && pq.top() < lr[i].first) {
            cnt++;
            sum = (sum + pq.top()) % mod;
            pq.pop();
        }
        ans += ((long long)cnt * lr[i].first % mod - sum + mod) % mod;
        ans %= mod;
        pq.push(lr[i].second);
    }
    return ans;
}

int main()
{
    cin >> N;
    vector<int> lef, rig, up, dw;
    vector<pair<int, int>> lr, ud;
    for(int i = 1; i <= N; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        lr.emplace_back(x1, x2);
        ud.emplace_back(y1, y2);
    }

    int ans = (solve(lr) + solve(ud)) % mod;
    cout << ans << "\n";
}