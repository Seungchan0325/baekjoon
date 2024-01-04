#include <iostream>
#include <algorithm>
#include <utility>

#include <vector>
#include <tuple>

using namespace std;

#define all(x) x.begin(), x.end()

struct Pos {
    int s, e;
    int idx;
};

const int INF = 1e9;

int n, m;
vector<Pos> lines;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n>>m;
    for(int i=1; i<=m; i++) {
        int a, b; cin>>a>>b;
        if(a < b) {
            lines.push_back({a, b, i});
        } else {
            lines.push_back({a - n, b, i});
            lines.push_back({a, b + n, i});
        }
    }

    sort(all(lines),  [](const Pos& a, const Pos& b) { if(a.s == b.s) return a.e > b.e; return a.s < b.s; });

    int last = -INF;
    vector<int> ans;
    for(auto& [s, e, idx] : lines) {
        if(last < e) {
            last = e;
            ans.push_back(idx);
        }
    }

    sort(all(ans));
    ans.erase(unique(all(ans)), ans.end());

    for(auto i : ans) cout<<i<<" ";
}