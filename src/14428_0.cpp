#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, m, arr[MAXN], tree[4*MAXN], tree_idx[4*MAXN];

void min(int idx) {
    if(tree[2*idx] <= tree[2*idx+1]) {
        tree[idx] = tree[2*idx];
        tree_idx[idx] = tree_idx[2*idx];
    } else {
        tree[idx] = tree[2*idx+1];
        tree_idx[idx] = tree_idx[2*idx+1];
    }
}

void tree_init(int s, int e, int idx) {
    if(s == e) {
        tree[idx] = arr[s];
        tree_idx[idx] = s;
        return;
    }

    int mid = (s + e) / 2;
    tree_init(s, mid, 2*idx);
    tree_init(mid+1, e, 2*idx+1);
    min(idx);
}

void tree_update(int s, int e, int idx, int pos, int v) {
    if(pos < s || e < pos) return;

    if(s == e) {
        tree[idx] = v;
        return;
    }

    int mid = (s + e) / 2;
    tree_update(s, mid, 2*idx, pos, v);
    tree_update(mid+1, e, 2*idx+1, pos, v);
    min(idx);
}

int tree_query(int s, int e, int idx, int l, int r) {
    if(r < s || e < l) return l;

    if(l <= s && e <= r) {
        return tree_idx[idx];
    }

    int mid = (s + e) / 2;
    int left = tree_query(s, mid, 2*idx, l, r);
    int right = tree_query(mid+1, e, 2*idx+1, l, r);

    if(arr[left] <= arr[right]) {
        return left;
    } else {
        return right;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin>>n;
    for(int i=0; i<n; i++) cin>>arr[i];

    tree_init(0, n-1, 1);
    
    cin>>m;
    while(m--) {
        int a, b, c; cin>>a>>b>>c;

        if(a == 1) {
            b--;
            arr[b] = c;
            tree_update(0, n-1, 1, b, c);
        } else {
            b--; c--;
            int idx = tree_query(0, n-1, 1, b, c);
            cout<<idx+1<<"\n";
        }
    }
}