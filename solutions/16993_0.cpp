#include <bits/stdc++.h>

using namespace std;

const long long INF = 1e10;
const long long MAXN = 100005;

long long n, m, tree[4*MAXN], ltree[4*MAXN], rtree[4*MAXN], lrtree[4*MAXN];

void update(long long pos, long long delta, long long start = 1, long long end = n, long long index = 1)
{
    if(end < pos || pos < start) return;

    if(start == end) {
        tree[index] += delta;
        ltree[index] += delta;
        rtree[index] += delta;
        lrtree[index] += delta;
        return;
    }

    long long mid = (start + end) / 2;
    update(pos, delta, start, mid, 2*index);
    update(pos, delta, mid+1, end, 2*index+1);

    ltree[index] = max(ltree[2*index], lrtree[2*index] + ltree[2*index+1]);
    rtree[index] = max(rtree[2*index+1], lrtree[2*index+1] + rtree[2*index]);
    lrtree[index] = lrtree[2*index] + lrtree[2*index+1];
    tree[index] = max({ltree[index], rtree[index], lrtree[index], rtree[2*index] + ltree[2*index + 1], tree[2*index], tree[2*index+1]});
}

tuple<long long, long long, long long, long long> query(long long left, long long right, long long start = 1, long long end = n, long long index = 1)
{
    if(end < left || right < start) return {-INF, -INF, -INF, -INF};

    if(left <= start && end <= right) return {ltree[index], rtree[index], lrtree[index], tree[index]};

    long long mid = (start + end) / 2;
    if(right <= mid) {
        return query(left, right, start, mid, 2*index);
    } else if(mid < left) {
        return query(left, right, mid+1, end, 2*index+1);
    } else {
        auto [ll, rl, lrl, max_l] = query(left, right, start, mid, 2*index);
        auto [lr, rr, lrr, max_r] = query(left, right, mid+1, end, 2*index+1);
        long long l = max(ll, lrl + lr);
        long long r = max(rr, lrr + rl);
        long long max_v = max({l, r, lrl + lrr, rl + lr, max_l, max_r});
        return {l, r, lrl + lrr, max_v};
    }
    assert(0);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n;
    for(long long i = 1; i <= n; i++) {
        long long x;
        cin >> x;
        update(i, x);
    }
    cin >> m;
    while(m--) {
        long long i, j;
        cin >> i >> j;
        long long result = get<3>(query(i, j));
        cout << result << "\n";
    }
}