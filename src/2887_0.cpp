#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

#define all(x) x.begin(), x.end()

using pii = pair<int, int>;

struct edge {
    int from;
    int to;
    int distance;
    bool operator<(const edge& other) { return distance < other.distance; }
};

int find(int x, vector<int>& root) {
    if(x == root[x]) return x;
    return root[x] = find(root[x], root);
}

bool isUnion(int x, int y, vector<int>& root) {
    x = find(x, root);
    y = find(y, root);

    return x == y;
}

void Union(int x, int y, vector<int>& root) {
    x = find(x, root);
    y = find(y, root);

    if(x <= y)  root[y] = x;
    else        root[x] = y;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int n;
    cin>>n;
    vector<pii> xs(n), ys(n), zs(n);
    for(int i=0; i<n; i++) {
        cin>>xs[i].first>>ys[i].first>>zs[i].first;
        xs[i].second = ys[i].second = zs[i].second = i;
    } 

    vector<edge> edges;
    sort(all(xs));
    sort(all(ys));
    sort(all(zs));

    for(int i=1; i<n; i++) {
        edges.push_back({xs[i-1].second, xs[i].second, abs(xs[i-1].first - xs[i].first)});
        edges.push_back({ys[i-1].second, ys[i].second, abs(ys[i-1].first - ys[i].first)});
        edges.push_back({zs[i-1].second, zs[i].second, abs(zs[i-1].first - zs[i].first)});
    }

    sort(all(edges));
    vector<int> root(n);
    for(int i=0; i<n; i++) root[i] = i;

    int sum = 0;
    for(int i=0; i<edges.size(); i++) {
        auto [from, to, distance] = edges[i];
        if(!isUnion(from, to, root)) {
            sum += distance;
            Union(from, to, root);
        }
    }

    cout<<sum;
}