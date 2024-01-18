#include <iostream>
#include <memory.h>

#include <vector>

using namespace std;


int n, dp[1000010][2], visit[1000010];
vector<int> tree[1000010], adjlist[1000010];

void make_tree(int node) {
    visit[node] = true;

    for(int next : adjlist[node])
        if(!visit[next]) {
            tree[node].push_back(next);
            make_tree(next);
        }
}

int min_early_adapters(int node, int is_node_early_adapter) {
    int& ret = dp[node][is_node_early_adapter];

    if(ret != -1) return ret;

    ret = is_node_early_adapter ? 1 : 0;
    for(int next : tree[node]) {
        if(is_node_early_adapter)
            ret += min(min_early_adapters(next, 0), min_early_adapters(next, 1));
        else
            ret += min_early_adapters(next, 1);
    }

    //printf("%d %d %d\n", node, is_node_early_adapter, ret);

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n;
    for(int i=0; i<n-1; i++) {
        int a, b; cin>>a>>b; a--; b--; if(a > b) swap(a, b);
        adjlist[a].push_back(b);
        adjlist[b].push_back(a);
    }

    make_tree(0);
    memset(dp, -1, sizeof(dp));
    int result = min(min_early_adapters(0, true), min_early_adapters(0, false));

    cout<<result;
}