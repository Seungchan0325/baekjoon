#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

int N, M;
vector<int> arr, tree;

int tree_init(int start, int end, int index) {
    if(start == end) {
        tree[index] = arr[start];
        return tree[index];
    }

    int mid = (start + end) / 2;

    tree[index] = min(tree_init(start, mid, index*2), tree_init(mid+1, end, index*2+1));
    return tree[index];
}

int tree_min(int start, int end, int left, int right, int index) {
    if(left > end || right < start) return INT_MAX;

    if(left <= start &&  end <= right) {
        return tree[index];
    }
    
    int mid = (start + end) / 2;
    return min(tree_min(start, mid, left, right, index*2), tree_min(mid+1, end, left, right, index*2+1));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>N>>M;
    arr.resize(N);
    tree.resize(N*4);
    for(int i=0; i<N; i++)
        cin>>arr[i];
    tree_init(0, N-1, 1);

    for(int i=0; i<M; i++) {
        int a, b;
        cin>>a>>b;
        a--; b--;

        int result = tree_min(0, N-1, a, b, 1);

        cout<<result<<"\n";
    }
}