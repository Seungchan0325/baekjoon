#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int to;
    int from;
    int weight;

    bool operator<(const Edge& other) {
        return weight < other.weight;
    }
};

int v, e, roots[10005];
vector<Edge> edges;

int find(int x) {
    if(roots[x] == x) return x;
    else return roots[x] = find(roots[x]);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>v>>e;
    edges.resize(e);
    for(auto& [to, from, weight] : edges) { cin>>to>>from>>weight; to--; from--; }

    for(int i=0; i<v; i++) roots[i] = i;

    int sum = 0;
    
    sort(edges.begin(), edges.end());
    for(auto& [to, from, weight] : edges) {
        int a = find(to);
        int b = find(from);
        if(a != b) {
            roots[b] = a;
            sum += weight;
        }
    }

    cout<<sum;
}