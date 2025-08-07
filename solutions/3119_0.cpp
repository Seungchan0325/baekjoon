#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;
const int inf = 2e9 + 5;

int N;

int main()
{
    cin >> N;
    map<array<int, 3>, int> idx;
    map<int, vector<pair<int, int>>, greater<>> fence;
    for(int i = 0; i < N; i++) {
        int x, w, h; cin >> x >> w >> h;
        idx[{x, x+w, h}] = i+1;
        fence[h].push_back({x, x+w});
    }
    
    vector<int> ans;
    set<pair<int, int>> sky;
    for(auto& [k, v] : fence) {
        sort(v.begin(), v.end(), [](pair<int, int> a, pair<int, int> b){
            if(a.first != b.first) return a.first < b.first;
            return a.second > b.second;
        });

        int i = -1;
        int j = 0;
        int l = inf;
        int r = -inf;
        priority_queue<pair<int, int>> pq;
        while(true) {
            while(pq.size()) pq.pop();
            if(i+1 == v.size()) break;

            i++;
            l = v[i].first;
            r = -inf;
            auto it = sky.lower_bound({l+1, 0});
            if(it != sky.begin() && v[i].first <= (--it)->second) {
                l = min(l, it->first);
                r = max(r, it->second);
                
                while(j < v.size() && v[j].first <= r) {
                    pq.emplace(v[j].second, j);
                    j++;
                }
                if(pq.empty() || pq.top().first <= r) continue;
                i = pq.top().second; pq.pop();
            }

            while(true) {
                l = min(l, v[i].first);
                r = max(r, v[i].second);

                auto it = sky.lower_bound({r+1, 0});
                if(it != sky.begin()) {
                    it--;
                    r = max(r, it->second);
                }

                ans.push_back(idx[{v[i].first, v[i].second, k}]);

                while(j < v.size() && v[j].first <= r) {
                    pq.emplace(v[j].second, j);
                    j++;
                }

                if(pq.empty() || pq.top().first <= r) {
                    auto it = sky.lower_bound({l, 0});
                    while(it != sky.begin()) {
                        it--;
                        if(l <= it->second) {
                            l = min(l, it->first);
                            r = max(r, it->second);
                            sky.erase(it);
                        } else {
                            break;
                        }
                        it = sky.lower_bound({l, 0});
                    }

                    it = sky.lower_bound({l, 0});
                    while(it != sky.end()) {
                        if(it->first <= r) {
                            l = min(l, it->first);
                            r = max(r, it->second);
                            sky.erase(it);
                        } else {
                            break;
                        }
                        it = sky.lower_bound({l, 0});
                    }

                    sky.insert({l, r});
                    break;
                }
                else {
                    i = pq.top().second; pq.pop();
                }
            }
        }
    }

    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());
    cout << ans.size() << "\n";
    for(auto i : ans) cout << i << " ";
}