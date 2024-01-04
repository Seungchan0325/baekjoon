#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
const int MAXK = 100005;
const int MAXM = 100005;

int sqrtN;

struct Q {
    int idx, s, e;
    bool operator < (Q& other) {
        if(s/sqrtN == other.s/sqrtN) return e < other.e;
        return s/sqrtN < other.s/sqrtN;
    }
};

int n, k, m, mmax, arr[MAXN], cnt[2*MAXN], ans[MAXM];
pair<int, int> lr[MAXK];
vector<int> table[MAXK];
Q queries[MAXM];

void update(int value, int delta_l, int delta_r) {
    auto& [l, r] = lr[value];
    int old_interval = table[value][r] - table[value][l];
    if(r < l) old_interval = -1;
    l += delta_l;
    r += delta_r;
    int interval = table[value][r] - table[value][l];
    if(r < l) interval = -1;

    cnt[old_interval+MAXN]--;
    cnt[interval+MAXN]++;

    mmax = max(interval, mmax);
    if(interval < old_interval && !cnt[mmax+MAXN])
        while(!cnt[(--mmax)+MAXN]);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    sqrtN = sqrt(n);
    for(int i = 1; i <= n; i++) cin >> arr[i];
    cin >> m;
    for(int i = 0; i < m; i++) {
        auto& [idx, s, e] = queries[i];
        cin >> s >> e;
        idx = i;
    }
    sort(queries, queries+m);

    for(int i = 1; i <= n; i++) {
        table[arr[i]].push_back(i);
        lr[arr[i]].second = table[arr[i]].size()-1;
    }

    for(int i = 1; i < MAXK; i++) {
        if(table[i].empty()) continue;
        int interval = table[i].back() - table[i].front();
        mmax = max(interval, mmax);
        cnt[interval+MAXN]++;
    }

    int s = 1, e = n;
    for(int i = 0; i < m; i++) {
        auto [idx, s1, e1] = queries[i];
        while(s < s1) update(arr[s++], 1, 0);
        while(s1 < s) update(arr[--s], -1, 0);
        while(e < e1) update(arr[++e], 0, 1);
        while(e1 < e) update(arr[e--], 0, -1);
        ans[idx] = mmax;
    }

    for(int i = 0; i < m; i++) cout << ans[i] << "\n";
}