#include <iostream>
#include <vector>

using namespace std;

long long N, M, K;
vector<long long> arr, tree;

long long tree_init(int start, int end, int index) {
    if(start == end) {
        tree[index] = arr[start];
        return tree[index];
    }

    int mid = (start + end) / 2;

    tree[index] = (tree_init(start, mid, index*2) * tree_init(mid+1, end, index*2+1))%1000000007;
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
    
    tree[index] = (tree[index*2] * tree[index*2+1])%1000000007;
}

long long tree_add(int start, int end, int index, int left, int right) {
    if(left > end || right < start) return 1;

    if(left <= start && end <= right) {
        return tree[index];
    }
    
    int mid = (start + end) / 2;
    return (tree_add(start, mid, index*2, left, right) * tree_add(mid+1, end, index*2+1, left, right))%1000000007;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>N>>M>>K;

    arr.resize(N);
    tree.resize(4*N);

    for(int i=0; i<N; i++) {
        cin>>arr[i];
    }
    tree_init(0, N-1, 1);
    for(int i=0; i<M+K; i++) {
        long long a, b, c;
        cin>>a>>b>>c;
        if(a == 1)
            tree_edit(0, N-1, 1, b-1, c);
        else
            cout<<tree_add(0, N-1, 1, b-1, c-1)<<"\n";
    }
}