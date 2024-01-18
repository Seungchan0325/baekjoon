#include <iostream>

using namespace std;

int N, ans, arr[1000], dp[1000], tree[4*1000];

void tree_update(int start, int end, int index, int n, int a) {
    if(n < start || end < n) return;

    if(start == end) {
        tree[index] = a;
        return;
    }

    int mid = (start + end) / 2;
    tree_update(start, mid, index*2, n, a);
    tree_update(mid+1, end, index*2+1, n, a);
    tree[index] = max(tree[index*2], tree[index*2+1]);
}

int tree_find(int start, int end, int index, int l, int r) {
    if(r < start || end < l) return 0;

    if(l <= start && end <= r) {
        return tree[index];
    }
    
    int mid = (start + end) / 2;

    return max(tree_find(start, mid, index*2, l, r),
        tree_find(mid+1, end, index*2+1, l, r));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>N;
    for(int i=0; i<N; i++)
        cin>>arr[i];

    for(int i=0; i<N; i++) {
        dp[i] = tree_find(0, 1000, 1, 0, arr[i]-1) + 1;
        tree_update(0, 1000, 1, arr[i], dp[i]);
        ans = max(dp[i], ans);
    }
    cout<<ans<<"\n";
}