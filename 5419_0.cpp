#include <iostream>
#include <algorithm>
#include <utility>
#include <memory.h>

using namespace std;

using pii = pair<int, int>;

int t, n;
unsigned int ans;
int tree[75000 * 4];
pii island[75000];

void tree_update(int start, int end, int index, int n, int a) {
    if(n < start || end < n) return;

    if(start == end) {
        tree[index] += a;
        return;
    }

    int mid = (start + end) / 2;

    tree_update(start, mid, index*2, n, a);
    tree_update(mid+1, end, index*2+1, n, a);
    tree[index] = tree[index*2] + tree[index*2+1];
}

int tree_query(int start, int end, int index, int qstart, int qend) {
    if(qend < start || end < qstart) return 0;

    if(qstart <= start && end <= qend) {
        return tree[index];
    }

    int mid = (start + end) / 2;
    return tree_query(start, mid, index*2, qstart, qend) + tree_query(mid+1, end, index*2+1, qstart, qend);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin>>t;
    while(t--) {
        cin>>n;
        for(int i=0; i<n; i++)
            cin>>island[i].first>>island[i].second;
        
        sort(island, island+n, [](const pii& a, const pii& b) { return a.second < b.second; });

        int tmp[75000] = {0};
        int m=0;
        for(int i=1; i<n; i++) {
            if(island[i-1].second != island[i].second) m++;
            tmp[i] = m;
        }
        for(int i=0; i<n; i++)
            island[i].second = tmp[i];
        
        sort(island, island+n, [](const pii& a, const pii& b) { return a.first < b.first || (a.first == b.first && a.second > b.second); });

        ans = 0;
        memset(tree, 0, sizeof(tree));
        for(int i=0; i<n; i++) {
            auto& cur = island[i];
            ans += tree_query(0, m, 1, cur.second, m);
            tree_update(0, m, 1, cur.second, 1);
        }
        cout<<ans<<"\n";
    }
}