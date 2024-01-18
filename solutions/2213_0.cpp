#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10005;

bool visited[MAXN];
int n, weights[MAXN], cache[MAXN];
vector<int> childs[MAXN], adjlist[MAXN];

void construct_tree(int node) {
    visited[node] = true;
    for(int child : adjlist[node])
        if(!visited[child]) {
            childs[node].push_back(child);
            construct_tree(child);
        }
}

int dfs(int node) {
    int& ret = cache[node];
    if(ret != -1) return ret;

    if(childs[node].empty()) return ret = weights[node];

    int not_included = 0, included = weights[node];
    for(int child : childs[node]) {
        not_included += dfs(child);

        for(int grandchild : childs[child])
            included += dfs(grandchild);
    }

    return ret = max(included, not_included);
}

vector<int> restructure(int node) {
    vector<int> ret;
    int not_included = 0;
    for(int child : childs[node])
        not_included += dfs(child);
    
    if(dfs(node) == not_included) {
        for(int child : childs[node]) {
            auto restructured = restructure(child);
            ret.insert(ret.end(), restructured.cbegin(), restructured.cend());
        }
    }
    else {
        ret.push_back(node);
        for(int child : childs[node])
            for(int grandchild : childs[child]) {
                auto restructured = restructure(grandchild);
                ret.insert(ret.end(), restructured.cbegin(), restructured.cend());
            }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n;
    for(int i=0; i<n; i++) cin>>weights[i];
    for(int i=0; i<n-1; i++) {
        int a, b; cin>>a>>b; a--; b--;
        adjlist[a].push_back(b);
        adjlist[b].push_back(a);
    }

    construct_tree(0);
    memset(cache, -1, sizeof(cache));
    int result = dfs(0);
    auto s = restructure(0);
    sort(s.begin(), s.end());

    cout<<result<<"\n";
    for(int i : s) cout<<i+1<<" ";
}