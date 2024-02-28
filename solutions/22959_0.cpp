#include <bits/stdc++.h>

using namespace std;
using llint = long long;

const int MAXN = 200005;
const int INF = 1e9 + 5;

struct T {
    llint sum;
    int mn;
    T() : sum(0), mn(0) {}
    T(llint _sum, int _mn) : sum(_sum), mn(_mn) {}
};

int N, M, arr[MAXN];
T tree[2*MAXN];

T merge(T a, T b)
{
    return T(a.sum + b.sum, arr[a.mn] < arr[b.mn] ? a.mn : b.mn);
}

void init()
{
    for(int i = 0; i < N; i++) {
        tree[i+N] = T(arr[i], i);
    }
    for(int i = N-1; i > 0; i--) {
        tree[i] = merge(tree[i<<1], tree[i<<1|1]);
    }
}

void update(int pos, int value)
{
    for(tree[pos+=N].sum = value; pos > 1; pos >>= 1) {
        tree[pos>>1] = merge(tree[pos], tree[pos^1]);
    }
}

T query(int l, int r)
{
    T ret(0, N);
    for(l+=N, r+=N; l <= r; l>>=1, r>>=1) {
        if(l&1) ret = merge(tree[l++], ret);
        if(~r&1) ret = merge(tree[r--], ret);
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    arr[N] = INF;
    init();
    cin >> M;
    while(M--) {
        int t, i, j;
        cin >> t >> i >> j;
        i--;
        if(t == 1) {
            arr[i] = j;
            update(i, j);
        } else {
            int l, r;

            int lo = -1, hi = i;
            while(lo + 1 < hi) {
                int mid = (lo + hi) >> 1;
                if(arr[query(mid, i).mn] < j) lo = mid;
                else hi = mid;
            }
            l = hi;

            lo = i, hi = N;
            while(lo + 1 < hi) {
                int mid = (lo + hi) >> 1;
                if(arr[query(i, mid).mn] >= j) lo = mid;
                else hi = mid;
            }
            r = lo;

            llint result = query(l, r).sum;
            cout << result << "\n";
        }
    }
}