#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

vector<int> lis(const vector<pii>& arr) {
    vector<pii> v;
    v.push_back({0, 987654321});

    vector<int> pos(arr.size());
    for(int i=0; i<arr.size(); i++) {
        if(v.back().second < arr[i].second) {
            v.push_back(arr[i]);
            pos[i] = v.size() - 1;
        } else {
            auto it = lower_bound(v.begin(), v.end(), arr[i], [](pii a, pii b){if(a.second == b.second) return a.first < b.first; return a.second < b.second; });
            *it = arr[i];
            pos[i] = it - v.begin();
        }
    }

    vector<int> ret;
    int last = v.size() - 1;
    for(int i = arr.size() - 1; i >= 0; i--) {
        if(last == pos[i]) {
            last--;
            ret.push_back(arr[i].first);
        }
    }

    reverse(ret.begin(), ret.end());

    return ret;
}

int main() {
    int n; cin>>n;
    vector<pii> lines(n);
    for(auto& [x, y] : lines) cin>>x>>y;
    sort(lines.begin(), lines.end());

    auto result = lis(lines);
    
    cout<<n - result.size()<<"\n";
    int last = 0;
    for(int i=0; i<n; i++) {
        if(!binary_search(result.begin(), result.end(), lines[i].first)) {
            cout<<lines[i].first<<"\n";
        }
    }
}