#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, inorder[MAXN], postorder[MAXN];

void preorder(int instart, int inend, int poststart, int postend) {
    if(inend < instart || postend < poststart) return;
    cout << postorder[postend] << " ";
    int idx = find(inorder + instart, inorder + inend, postorder[postend]) - inorder;

    int numleft = idx - instart;
    preorder(instart, idx-1, poststart, poststart + numleft - 1);
    preorder(idx+1, inend, poststart + numleft, postend-1);
}

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) cin >> inorder[i];
    for(int i = 0; i < n; i++) cin >> postorder[i];

    preorder(0, n-1, 0, n-1);
}