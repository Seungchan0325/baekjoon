#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 10000;

int n, depths[MAXN], parents[MAXN], node1, node2;
vector<int> tree[MAXN];

void set_tree(int idx, int parent, int depth) {
    parents[idx] = parent;
    depths[idx] = depth;
    for(auto next : tree[idx]) {
        set_tree(next, idx, depth + 1);
    }
}

int LCA(int node1, int node2) {
    while(depths[node1] < depths[node2]) node2 = parents[node2];
    while(depths[node1] > depths[node2]) node1 = parents[node1];
    while(node1 != node2) { node1 = parents[node1]; node2 = parents[node2]; }
    return node1;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin>>t;
    while(t--) {
        cin>>n;
        vector<bool> appeared(n);
        for(int i=0; i<n-1; i++) {
            int a, b; cin>>a>>b; a--; b--;
            tree[a].push_back(b);
            appeared[b] = true;
        }
        cin>>node1>>node2; node1--; node2--;

        int root = find(appeared.begin(), appeared.end(), false) - appeared.begin();

        set_tree(root, root, 0);

        int result = LCA(node1, node2);

        cout<<result + 1<<"\n";

        for(int i=0; i<n; i++) {
            tree[i].clear();
        }
    }
}