#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 1000005;

struct node {
    ll sum;
    int mx;
    int mx2;
    int cntmx;
};

int n, m, arr[MAXN];
node tree[4*MAXN];

node f(node a, node b)
{
    if(a.mx == b.mx) return {a.sum + b.sum, a.mx, max(a.mx2, b.mx2), a.cntmx + b.cntmx};
    if(a.mx > b.mx) swap(a, b);
    return {a.sum + b.sum, b.mx, max(a.mx, b.mx2), b.cntmx};
}

node init(int start, int end, int index)
{
    if(start == end) {
        return tree[index] = {arr[start], arr[start], -1, 1};
    }
    int mid = (start + end) / 2;
    return tree[index] = f(init(start, mid, 2*index), init(mid+1, end, 2*index+1));
}

void push(int start, int end, int index)
{
    if(start == end) return;
    for(auto i : {2 * index, 2 * index + 1}) {
        if(tree[index].mx < tree[i].mx) {
            tree[i].sum -= (ll)tree[i].cntmx * (tree[i].mx - tree[index].mx);
            tree[i].mx = tree[index].mx;
        }
    }
}

void update(int start, int end, int index, int left, int right, int v)
{
    push(start, end, index);
    if(end < left || right < start || tree[index].mx <= v) return;

    if(left <= start && end <= right && tree[index].mx2 < v) {
        tree[index].sum -= (ll)tree[index].cntmx * (tree[index].mx - v);
        tree[index].mx = v;
        push(start, end, index);
        return;
    }

    int mid = (start + end) / 2;
    update(start, mid, 2*index, left, right, v);
    update(mid+1, end, 2*index+1, left, right, v);
    tree[index] = f(tree[2*index], tree[2*index+1]);
}

int getmx(int start, int end, int index, int left, int right)
{
    push(start, end, index);
    if(end < left || right < start) return 0;
    if(left <= start && end <= right) return tree[index].mx;
    int mid = (start + end) / 2;
    return max(getmx(start, mid, 2*index, left, right), getmx(mid+1, end, 2*index+1, left, right));
}

ll getsum(int start, int end, int index, int left, int right)
{
    push(start, end, index);
    if(end < left || right < start) return 0;
    if(left <= start &&  end <= right) return tree[index].sum;
    int mid = (start + end) / 2;
    return getsum(start, mid, 2*index, left, right) + getsum(mid+1, end, 2*index+1, left, right);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    init(1, n, 1);
    cin >> m;
    for(int i = 0; i < m; i++) {
        int type, left, right;
        cin >> type >> left >> right;

        if(type == 1) {
            int x;
            cin >> x;
            update(1, n, 1, left, right, x);
        } else if(type == 2) {
            int result = getmx(1, n, 1, left, right);
            cout << result << "\n";
        } else if(type == 3) {
            ll result = getsum(1, n, 1, left, right);
            cout << result << "\n";
        }
    }
}