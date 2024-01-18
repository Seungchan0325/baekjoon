#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
const int MAXM = 100005;
const int MAXA = 100000;

int sqrtN;

struct Query {
    int s, e;
    int idx;
    bool operator < (const Query& rhs) const
    {
        if(s / sqrtN != rhs.s / sqrtN) return s / sqrtN < rhs.s / sqrtN;
        return e < rhs.e;
    }
};

long long n, k, m, arr[MAXN], ans[MAXM];
int fenwick[MAXA + 1];
Query queries[MAXM];

int query(int i) {
    if(i < 0) return 0;
    if(MAXA < i) i = MAXA;
    int ret = 0;
    while(i > 0) {
        ret += fenwick[i];
        i -= (i & -i);
    }
    return ret;
}

void update(int i, int v) {
    while(i <= MAXA) {
        fenwick[i] += v;
        i += (i & -i);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> n >> k;
    sqrtN = sqrt(n);
    for(int i = 0; i < n; i++) cin >> arr[i];
    cin >> m;
    for(int i = 0; i < m; i++) {
        cin >> queries[i].s >> queries[i].e;
        queries[i].s--;
        queries[i].e--;
        queries[i].idx = i;
    }
    sort(queries, queries + m);

    long long cnt = 0;
    int l = queries[0].s;
    int r = l - 1;

    auto add = [&](int i) {
        cnt += query(arr[i] + k) - query(arr[i] - k - 1);
        update(arr[i], 1);
    };

    auto sub = [&](int i) {
        update(arr[i], -1);
        cnt -= query(arr[i] + k) - query(arr[i] - k - 1);
    };

    for(int i = 0; i < m; i++) {
        while(queries[i].s < l) add(--l);
        while(l < queries[i].s) sub(l++);
        while(r < queries[i].e) add(++r);
        while(queries[i].e < r) sub(r--);
        ans[queries[i].idx] = cnt;
    }
    for(int i = 0; i < m; i++) cout << ans[i] << "\n";
}