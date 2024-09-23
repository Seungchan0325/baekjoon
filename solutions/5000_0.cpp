#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int N, A[MAXN], B[MAXN], tree[MAXN];

void update(int x, int v)
{
    while(x <= N) {
        tree[x] += v;
        x += x & -x;
    }
}

int query(int x)
{
    int ret = 0;
    while(x > 0) {
        ret += tree[x];
        x -= x & -x;
    }
    return ret;
}

int inversion_counting(int n, int a[])
{
    int ret = 0;
    memset(tree, 0, sizeof(tree));
    for(int i = 1; i <= n; i++) {
        ret += query(N) - query(a[i]);
        ret %= 2;
        update(a[i], 1);
    }
    return ret;
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> A[i];
    }
    for(int i = 1; i <= N; i++) {
        cin >> B[i];
    }

    if(inversion_counting(N, A) == inversion_counting(N, B)) cout << "Possible";
    else cout << "Impossible";
}