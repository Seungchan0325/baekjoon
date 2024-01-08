#include <bits/stdc++.h>

using namespace std;

int n, m, X, Y, cities[25][105];

vector<int> compute_vertical(int limit, int horizon)
{
    vector<int> verticals;
    vector<int> sum(X + 1);
    for(int c = 0; c <= m; c++) {
        int last = 0;
        bool is_need_new_vertical = false;
        for(int r = 0; r <= n; r++) {
            sum[last] += cities[r][c];

            if(sum[last] > limit) {
                is_need_new_vertical = true;
                break;
            }

            if(horizon & (1<<r)) {
                last++;
            }
        }

        if(is_need_new_vertical) {
            verticals.push_back(c);

            fill(sum.begin(), sum.end(), 0);
            last = 0;
            for(int r = 0; r <= n; r++) {
                sum[last] += cities[r][c];

                if(horizon & (1<<r)) {
                    last++;
                }
            }
        }

        if(verticals.size() > Y) return verticals;
    }

    return verticals;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> m;
    cin >> X >> Y;
    for(int r = 0; r <= n; r++) {
        for(int c = 0; c <= m; c++) {
            cin >> cities[r][c];
        }
    }

    int ans = 20000005;
    int ans_horizon = -1;
    vector<int> ans_vertical;
    for(int horizon = 0; horizon < (1<<(n+1)); horizon++) {
        int popcount = __builtin_popcount(horizon);
        if(popcount != X) continue;

        if(compute_vertical(ans - 1, horizon).size() > Y) continue;

        int lo = 0;
        for(int c = 0; c <= m; c++) {
            int sum = 0;
            for(int r = 0; r <= n; r++) {
                sum += cities[r][c];
                if(horizon & (1<<r)) {
                    lo = max(sum - 1, lo);
                    sum = 0;
                }
            }
        }

        int hi = ans;
        while(lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            if(compute_vertical(mid, horizon).size() > Y) lo = mid;
            else hi = mid;
        }

        ans = hi;
        ans_horizon = horizon;
        ans_vertical = compute_vertical(hi, horizon);
    }

    if(ans_vertical.size() < Y) {
        for(int i = 1; i <= m && ans_vertical.size() < Y; i++) {
            if(find(ans_vertical.begin(), ans_vertical.end(), i) != ans_vertical.end()) continue;
            ans_vertical.push_back(i);
        }
    }
    sort(ans_vertical.begin(), ans_vertical.end());
    assert(ans_vertical.size() == Y);

    for(int i = 0; i <= n; i++) {
        if(ans_horizon & (1<<i)) {
            cout << i + 1 << " ";
        }
    }
    cout << "\n";
    for(auto i : ans_vertical) {
        cout << i << " ";
    }
    cout << "\n";
    cout << ans;
}