#include <bits/stdc++.h>

using namespace std;

const int MAX = 1000001;

int tree[4*MAX];

void update(int s, int e, int idx, int pos, int delta) {
    if(pos < s || e < pos) return;

    if(s == e) {
        tree[idx] += delta;
        return;
    }

    int mid = (s + e) / 2;
    update(s, mid, 2*idx, pos, delta);
    update(mid+1, e, 2*idx+1, pos, delta);

    tree[idx] = tree[2*idx] + tree[2*idx+1];
}

int query(int s, int e, int idx, int n) {
    if(s == e || n == 0) return s;

    int mid = (s + e) / 2;
    if(n <= tree[2*idx])
        return query(s, mid, 2*idx, n);
    else
        return query(mid+1, e, 2*idx+1, n-tree[2*idx]);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n; cin>>n;
    while(n--) {
        int a, b, c;
        cin>>a;
        
        if(a == 1) {
            cin>>b;

            int q = query(1, MAX-1, 1, b);
            update(1, MAX-1, 1, q, -1);
            cout<<q<<"\n";
        } else {
            cin>>b>>c;

            update(1, MAX-1, 1, b, c);
        }
    }
}