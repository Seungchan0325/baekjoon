#include <bits/stdc++.h>

using namespace std;

int main() {
    int n; cin >> n;
    vector<tuple<int, int, int>> tree(n);
    for(auto& [x, y, l] : tree) cin >> x >> y >> l;
    
    vector<int> xs;
    vector<int> ys;
    for(const auto& [x, y, l] : tree) {
        xs.push_back(x);
        ys.push_back(y);
    }
    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());

    int ans = 987654321;
    for(int l = 0; l < xs.size(); l++) {
        for(int r = l; r < xs.size(); r++) {
            for(int b = 0; b < ys.size(); b++) {
                for(int t = b; t < ys.size(); t++) {
                    priority_queue<int> pq;
                    int cnt = 0;
                    int sum = 0;
                    for(const auto& [x, y, len] : tree) {
                        if(xs[l] <= x && x <= xs[r] && ys[b] <= y && y <= ys[t]) {
                            pq.push(len);
                        } else {
                            sum += len;
                            cnt++;
                        }
                    }
                    int round = 2*(xs[r]-xs[l]) + 2*(ys[t]-ys[b]);
                    while(round > sum && !pq.empty()) {
                        sum += pq.top(); pq.pop();
                        cnt++;
                    }

                    ans = min(cnt, ans);
                }
            }
        }
    }

    cout << ans;
}