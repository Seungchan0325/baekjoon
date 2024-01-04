#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

const int MAXN = 100005;

bool visited[MAXN];
int n, k, arr[MAXN];
pii sorted[MAXN];
int parent[MAXN];

struct edge {
    int idx;
    int bit;
};

void restruct(int node) {
    if(node == -1) return;
    restruct(parent[node]);
    cout<<node+1<<" ";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> k;
    for(int i=0; i<n; i++) {
        sorted[i].second = i;
        for(int j=0; j<k; j++) {
            char bit; cin>>bit;
            if(bit == '1')
                arr[i] += 1 << j;
        }
        sorted[i].first = arr[i];
    }
    sort(sorted, sorted + n);

    memset(parent, -1, sizeof(parent));
    queue<edge> q;
    q.push({0, arr[0]});
    visited[0] = true;
    while(!q.empty()) {
        int idx = q.front().idx;
        int bit = q.front().bit;
        q.pop();
        for(int i=0; i<k; i++) {
            int next_bit = bit ^ (1<<i);
            auto next = *upper_bound(sorted, sorted + n, make_pair(next_bit, 0));
            if(next.first != next_bit || visited[next.second]) continue;
            visited[next.second] = true;
            parent[next.second] = idx;
            q.push({next.second, next.first});
        }
    }

    int j; cin>>j;
    for(int i=0; i<j; i++) {
        int idx; cin>>idx; idx--;
        if(parent[idx] == -1) cout<<-1;
        else restruct(idx);
        cout<<"\n";
    }
}