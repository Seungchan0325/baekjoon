#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int from;
    int to;
    int weight;

    bool operator<(const Edge& other) {
        return weight < other.weight;
    }
};

int n, m, roots[100005];
Edge edges[1000005];

int find(int x) {
    if(roots[x] == x) return x;
    else return roots[x] = find(roots[x]);
}

int is_unioned(int x, int y) {
    x = find(x);
    y = find(y);

    return x == y;
}

void Union(int x, int y) {
    x = find(x);
    y = find(y);

    roots[y] = x;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n>>m;
    for(int i=0; i<m; i++) cin>>edges[i].from>>edges[i].to>>edges[i].weight;

    for(int i=0; i<n; i++) roots[i] = i;
    sort(edges, edges + m);

    int last = 0;
    int sum = 0;
    for(int i=0; i<m; i++) {
        if(!is_unioned(edges[i].from, edges[i].to)) {
            sum += last;
            last = edges[i].weight;
            Union(edges[i].from, edges[i].to);
        }
    }

    cout<<sum;
}