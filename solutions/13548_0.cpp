#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
const int MAXA = 100005;
const int MAXM = 100005;

int rtN;

struct Q {
    int idx, s, e;
    bool operator < (Q other) {
        if(s/rtN == other.s/rtN) return e < other.e;
        return s/rtN < other.s/rtN;
    }
};

int n, m, mmax, arr[MAXN], ans[MAXM], cnt[MAXA], ccnt[2*MAXN];
Q queries[MAXM];

void update(int idx, int delta) {
    ccnt[cnt[idx]+MAXN]--;
    cnt[idx] += delta;
    ccnt[cnt[idx]+MAXN]++;
    mmax = max(cnt[idx], mmax);
    if(ccnt[mmax+MAXN] == 0) mmax--;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    rtN = sqrt(n);
    for(int i = 1; i <= n; i++) cin >> arr[i];
    cin >> m;
    for(int i = 0; i < m; i++) {
        cin >> queries[i].s >> queries[i].e;
        queries[i].idx = i;
    }
    sort(queries, queries + m);

    vector<int> v;
    v.assign(arr, arr+n);
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    ccnt[MAXN] = v.size();
    int s = queries[0].s, e = queries[0].e;
    for(int i = s; i <= e; i++) {
        update(arr[i], 1);
    }
    ans[queries[0].idx] = mmax;

    for(int i = 1; i < m; i++) {
        auto [idx, s1, e1] = queries[i];
        while(s < s1) update(arr[s++], -1);
        while(s1 < s) update(arr[--s], 1);
        while(e < e1) update(arr[++e], 1);
        while(e1 < e) update(arr[e--], -1);
        ans[idx] = mmax;
    }

    for(int i = 0; i < m; i++) cout << ans[i] << "\n";
}