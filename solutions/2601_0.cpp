#include <bits/stdc++.h>

using namespace std;

struct Shift {
    int x;
    int lr, ry;
    int value;

    bool operator<(const Shift& other) {
        if(x == other.x) return value > other.value;
        return x < other.x;
    }
};

int tree[4000005], lazy[4000005];

void propagation(int start, int end, int node) {
    if(lazy[node] != 0) {
        tree[node] += lazy[node];
        if(start != end) {
            lazy[2*node] += lazy[node];
            lazy[2*node+1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void update_range(int start, int end, int node, int left, int right, int value) {
    propagation(start, end, node);
    if(right < start || end < left) return;

    if(left <= start && end <= right) {
        tree[node] += value;
        if(start != end) {
            lazy[2*node] += value;
            lazy[2*node+1] += value;
        }
        return;
    }

    int mid = (start + end) / 2;
    update_range(start, mid, 2*node, left, right, value);
    update_range(mid+1, end, 2*node+1, left, right, value);
    tree[node] = max(tree[2*node], tree[2*node+1]);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int left, top, right, bottom, carpet, stain;
    cin>>left>>top>>right>>bottom;
    cin>>carpet;
    cin>>stain;
    vector<Shift> shifts;
    for(int i=0; i<stain; i++) {
        int l, t, r, b;
        cin>>l>>t>>r>>b;
        if(r - l > carpet || t - b > carpet) continue;
        int lx = max(left, r - carpet);
        int rx = l;
        int ly = max(bottom, t - carpet);
        int ry = b;
        shifts.push_back({lx, ly, ry, 1});
        shifts.push_back({rx, ly, ry, -1});
    }

    sort(shifts.begin(), shifts.end());
    
    int ans = 0;
    for(auto [x, ly, ry, value] : shifts) {
        update_range(bottom, top, 1, ly, ry, value);
        ans = max(tree[1], ans);
    }
    cout<<ans;
}