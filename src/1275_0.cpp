#include <iostream>
#include <vector>

using namespace std;

long long N, Q;
vector<long long> arr, tree;

long long tree_init(int start, int end, int index) {
    if(start == end) {
        tree[index] = arr[start];
        return tree[index];
    }

    int mid = (start + end) / 2;

    tree[index] = tree_init(start, mid, index*2) + tree_init(mid+1, end, index*2+1);
    return tree[index];
}

void tree_edit(int start, int end, int index, int n, long long a) {
    if(n < start || n > end) return;
    if(start == end) {
        tree[index] = a;
        return;
    }

    int mid = (start + end) / 2;
    tree_edit(start, mid, index*2, n, a);
    tree_edit(mid+1, end, index*2+1, n, a);
    
    tree[index] = tree[index*2] + tree[index*2+1];
}

long long tree_add(int start, int end, int index, int left, int right) {
    if(left > end || right < start) return 0;

    if(left <= start && end <= right) {
        return tree[index];
    }
    
    int mid = (start + end) / 2;
    return tree_add(start, mid, index*2, left, right) + tree_add(mid+1, end, index*2+1, left, right);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>N>>Q;

    arr.resize(N);
    tree.resize(4*N);

    for(int i=0; i<N; i++) {
        cin>>arr[i];
    }
    tree_init(0, N-1, 1);

    for(int i=0; i<Q; i++) {
        long long x, y, a, b;
        cin>>x>>y>>a>>b;
        x--; y--; a--;
        long long result = tree_add(0, N-1, 1, min(x, y), max(x, y));
        tree_edit(0, N-1, 1, a, b);
        cout<<result<<"\n";
    }
}