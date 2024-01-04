#include <iostream>
#include <vector>

using namespace std;

int N, M;
vector<long long> tree;

void tree_update(int start, int end, int index, int n, long long a) {
    if(n < start || end < n) return;

    if(start == end) {
        tree[index] = a;
        return;
    }

    int mid = (start + end) / 2;
    tree_update(start, mid, index*2, n, a);
    tree_update(mid+1, end, index*2+1, n, a);
    tree[index] = tree[index*2] + tree[index*2+1];
}

long long tree_sum(int start, int end, int index, int left, int right) {
    if(right < start || end < left) return 0;

    if(left <= start && end <= right) {
        return (long long)tree[index];
    }

    int mid = (start + end) / 2;
    return tree_sum(start, mid, index*2, left, right) + tree_sum(mid+1, end, index*2+1, left, right);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>N>>M;
    tree.resize(4*N);
    
    for(int i=0; i<M; i++) {
        int a, b, c;
        cin>>a>>b>>c;

        if(a == 0) {
            if(b > c) swap(b, c);
            long long result = tree_sum(0, N-1, 1, b-1, c-1);
            cout<<result<<"\n";
        } else if(a == 1) {
            tree_update(0, N-1, 1, b-1, c);
        }
    }
}