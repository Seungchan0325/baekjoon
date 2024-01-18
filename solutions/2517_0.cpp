#include <iostream>
#include <algorithm>

using namespace std;
using pii = pair<int, int>;

int n, arr[500000], tree[500001*4] = {0};

void tree_update(int start, int end, int index, int idx, int value) {
    if(idx < start || end < idx) return;

    if(start == end) {
        tree[index] += value;
        return;
    }

    int mid = (start + end) / 2;

    tree_update(start, mid, index*2, idx, value);
    tree_update(mid+1, end, index*2+1, idx, value);
    tree[index] = tree[index*2] + tree[index*2+1];
}

int tree_sum(int start, int end, int index, int l, int r) {
    if(r < start || end < l) return 0;

    if(l <= start && end <= r) {
        return tree[index];
    }

    int mid = (start + end) / 2;

    return tree_sum(start, mid, index*2, l, r) + tree_sum(mid+1, end, index*2+1, l, r);
}

void update(int idx, int value) {
    tree_update(0, n, 1, idx, value);
}

int sum(int l, int r) {
    return tree_sum(0, n, 1, l, r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin>>n;
    for(int i=0; i<n; i++) {
        cin>>arr[i];
    }

    {   //Coordination compression
        int tmp[500000];
        for(int i=0; i<n; i++)
            tmp[i] = arr[i];
        sort(tmp, tmp+n);
        for(int i=0; i<n; i++)
            arr[i] = lower_bound(tmp, tmp+n, arr[i]) - tmp + 1;
    }

    int ans;
    for(int i=0; i<n; i++) {
        ans = sum(arr[i], n);
        update(arr[i], 1);
        cout<<ans+1<<"\n";
    }
}