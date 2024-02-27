#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
const int MAXM = 100005;

int sqrtN;

struct Q {
    int s, e, idx;
    bool operator < (const Q& other) const
    {
        if(s/sqrtN != other.s/sqrtN) return s/sqrtN < other.s/sqrtN;
        return e < other.e;
    }
};

int N, M, sz, arr[MAXN], tree[MAXN];
long long ans[MAXM];
Q queries[MAXM];

void update(int pos, int delta)
{
    while(pos <= sz) {
        tree[pos] += delta;
        pos += (pos & -pos);
    }
}

int query(int pos)
{
    int ret = 0;
    while(pos > 0) {
        ret += tree[pos];
        pos -= (pos & -pos);
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    sqrtN = sqrt(N);
    vector<int> v;
    for(int i = 0; i < N; i++) {
        cin >> arr[i];
        v.push_back(arr[i]);
    }

    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    sz = v.size();
    for(int i = 0; i < N; i++) {
        arr[i] = lower_bound(v.begin(), v.end(), arr[i]) - v.begin() + 1;
    }

    for(int i = 0; i < M; i++) {
        queries[i].idx = i;
        cin >> queries[i].s >> queries[i].e;
        queries[i].s--;
        queries[i].e--;
    }

    sort(queries, queries + M);

    int s = queries[0].s, e = queries[0].s - 1;
    long long cnt = 0;
    for(int i = 0; i < M; i++) {
        while(s < queries[i].s) {
            update(arr[s], -1);
            cnt -= query(arr[s]-1);
            s++;
        }
        while(queries[i].s < s) {
            s--;
            cnt += query(arr[s]-1);
            update(arr[s], 1);
        }
        while(e < queries[i].e) {
            e++;
            cnt += query(sz) - query(arr[e]);
            update(arr[e], 1);
        }
        while(queries[i].e < e) {
            update(arr[e], -1);
            cnt -= query(sz) - query(arr[e]);
            e--;
        }
        ans[queries[i].idx] = cnt;
    }

    for(int i = 0; i < M; i++) {
        cout << ans[i] << "\n";
    }
}