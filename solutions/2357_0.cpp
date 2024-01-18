#include <iostream>
#include <utility>

using namespace std;

const int INF = 1e9;

pair<int, int> tree[400005];

pair<int, int> minmax(const pair<int, int>& x, const pair<int, int>& y) {
    pair<int, int> ret;
    ret.first = min(x.first, y.first);
    ret.second = max(x.second, y.second);
    return ret;
}

void tree_update(int st, int en, int idx, int n, int v) {
    if(en < n || n < st) return;

    if(st == en) {
        tree[idx] = make_pair(v, v);
        return;
    }

    int mid = (st + en) / 2;
    tree_update(st, mid, idx*2, n, v);
    tree_update(mid+1, en, idx*2+1, n, v);
    tree[idx] = minmax(tree[idx*2], tree[idx*2+1]);
}

pair<int, int> tree_query(int st, int en, int idx, int qst, int qen) {
    if(en < qst || qen < st) return make_pair(INF, -INF);

    if(qst <= st && en <= qen)
        return tree[idx];

    int mid = (st + en) / 2;
    return minmax(tree_query(st, mid, idx*2, qst, qen), tree_query(mid+1, en, idx*2+1, qst, qen));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int n, m; cin>>n>>m;
    for(int i=0; i<n; i++) {
        int a; cin>>a;
        tree_update(0, n-1, 1, i, a);
    }

    for(int i=0; i<m; i++) {
        int a, b; cin>>a>>b; a--; b--;

        auto minmax = tree_query(0, n-1, 1, a, b);
        cout<<minmax.first<<" "<<minmax.second<<"\n";
    }
}