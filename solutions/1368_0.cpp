#include <iostream>
#include <algorithm>
#include <utility>
#include <queue>

using namespace std;

using node = pair<int, pair<int, int>>;

int n, costs[301][301];
int parent[301];
vector<node> edges;

int find(int x) {
    if(x == parent[x])
        return x;
    else
        return parent[x] = find(parent[x]);
}

bool Union(int x, int y) {
    int px, py;
    px = find(x);
    py = find(y);
    if(px != py) {
        parent[py] = parent[px];
        return true;
    }
    return false;
}

int main() {
    cin>>n;
    for(int i=1; i<=n; i++) {
        int tmp;
        cin>>tmp;
        edges.push_back({tmp, {0, i}});
    }
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++) {
            int tmp;
            cin>>tmp;
            edges.push_back({tmp, {i, j}});
        }

    for(int i=1; i<=n; i++)
        parent[i] = i;

    sort(edges.begin(), edges.end(), less<>());
    
    int total = 0;
    for(auto i:edges) {
        //cout<<i.first<<" "<<i.second.first<<" "<<i.second.second<<endl;
        if(Union(i.second.first, i.second.second)) {
            total += i.first;
        }
    }

    cout<<total<<endl;
}