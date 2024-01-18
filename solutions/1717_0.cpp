#include <iostream>
#include <vector>

using namespace std;

int n, m;
int op, a, b;
vector<int> root;

int find(int x) {
    if(root[x] == -1) {
        return x;
    } else {
        return root[x] = find(root[x]);
    }
}

// x < y
void Union(int x, int y) {
    int a = find(x);
    int b = find(y);

    root[b] = a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>n>>m;
    
    root.resize(n+1, -1);
    for(int i=0; i<m; i++) {
        cin>>op>>a>>b;
        
        if(b < a) swap(a, b);
        if(op == 0) {
            if(find(a) != find(b))
                Union(a, b);
        } else if(op == 1) {
            if(find(a) == find(b))
                cout<<"YES\n";
            else
                cout<<"NO\n";
        }
    }
}