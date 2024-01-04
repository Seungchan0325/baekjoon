#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

using pii = pair<int, int>;

int overlap(vector<pii> l) {
    vector<int> zip;
    for(auto i : l) {
        zip.push_back(i.first);
        zip.push_back(i.second);
    }

    sort(zip.begin(), zip.end());
    zip.erase(unique(zip.begin(), zip.end()), zip.end());

    vector<int> commands(zip.size() + 1);
    for(auto i : l) {
        int l = lower_bound(zip.begin(), zip.end(), i.first) - zip.begin();
        int r = lower_bound(zip.begin(), zip.end(), i.second) - zip.begin();
        if(r < l) swap(l, r);
        commands[l]++;
        commands[r]--;
    }

    int ret = 0;
    int sum = 0;
    for(int i=0; i<zip.size(); i++) {
        sum += commands[i];
        ret = max(ret, sum);
    }
    return ret;
}

int main() {
    int n; cin>>n;
    vector<pii> v(n);
    for(auto& i : v) cin>>i.first>>i.second;

    int px = v[0].first, py = v[0].second;
    vector<pii> lx, ly;
    for(int i=1; i<n+1; i++) {
        if(px != v[i%n].first) lx.push_back({px, v[i%n].first});
        if(py != v[i%n].second) ly.push_back({py, v[i%n].second});
        px = v[i%n].first;
        py = v[i%n].second;
    }

    int result = max(overlap(lx), overlap(ly));

    cout<<result;
}