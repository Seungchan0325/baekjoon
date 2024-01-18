#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100000;

bool visited[MAXN];
int n, cache[MAXN][17];
vector<int> adjlist[MAXN], childs[MAXN];

void construct_tree(int node) {
    visited[node] = true;
    for(int child : adjlist[node])
        if(!visited[child]) {
            childs[node].push_back(child);
            construct_tree(child);
        }
}

int dfs(int node, int node_color) {
    int& ret = cache[node][node_color];
    if(ret != -1) return ret;

    ret = node_color + 1;
    for(int child : childs[node]) {
        int min_cost = 987654321;
        for(int color = 0; color < 17; color++) {
            if(node_color == color) continue;
            min_cost = min(dfs(child, color), min_cost);
        }
        ret += min_cost;
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n;
    for(int i=0; i<n-1; i++) {
        int a, b; cin>>a>>b; a--; b--;
        adjlist[a].push_back(b);
        adjlist[b].push_back(a);
    }

    construct_tree(0);

    memset(cache, -1, sizeof(cache));
    int result = 987654321;
    for(int color = 0; color < 17; color++) {
        result = min(dfs(0, color), result);
    }
    cout<<result;
}