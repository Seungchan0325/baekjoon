#include <bits/stdc++.h>

using namespace std;

bool query(int i, int j)
{
    cout << "? " << i << " " << j << " " << endl;
    char c;
    cin >> c;
    return c == '<';
}

int tree[202020];

int solve(int n)
{
    for(int i=0; i < n; i++) tree[i+n] = i;
    for(int i=n-1; i>0; i--) tree[i] = query(tree[i<<1], tree[i<<1|1]) ? tree[i<<1|1] : tree[i<<1];
    int i = 1;
    int x = -1;
    while(i < n) {
        if(tree[i] == tree[i<<1|1]) {
            if(x == -1) x = tree[i<<1];
            else x = query(x, tree[i<<1]) ? tree[i<<1] : x;
            i<<=1;
            i|=1;
        } else {
            if(x == -1) x = tree[i<<1|1];
            else x = query(x, tree[i<<1|1]) ? tree[i<<1|1] : x;
            i<<=1;
        }
    }
    return x;
}

int main()
{
    int n;
    cin >> n;
    assert(n != 1);
    int ans = solve(n);
    cout << "! " << ans << " " << endl;
}