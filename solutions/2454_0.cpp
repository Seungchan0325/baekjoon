#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

const int MAXN = 300005;

int n, k;
vector<int> childs[MAXN];

pii dfs(int node, int parent) {
    int sum = 0;
    vector<pii> v;
    for(auto child : childs[node]) {
        if(child == parent) continue;
        v.push_back(dfs(child, node));
        sum += v.back().first;
    }
    sort(v.begin(), v.end(), [](pii a, pii b) { return a.second < b.second; });

    pii ret = {sum + 1, 1};
    if(v.size() >= 1 && v[0].second < k + 1) ret = min(pii(sum, v[0].second + 1), ret);
    if(v.size() >= 2 && v[0].second + v[1].second < k + 1) ret = min(pii(sum - 1, k + 1), ret);

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n>>k;
    for(int i=0; i<n-1; i++) {
        int a, b; cin>>a>>b;
        childs[a].push_back(b);
        childs[b].push_back(a);
    }

    auto result = dfs(1, -1);
    cout<<result.first;
}