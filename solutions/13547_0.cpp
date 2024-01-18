#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
const int MAXM = 100005;
const int MAXA = 1000005;

int sq;

struct Q {
    int i, s, e;
    bool operator < (Q& other) {
        if(s/sq == other.s/sq) return e < other.e;
        return s/sq < other.s/sq;
    }
};

int n, m, arr[MAXN], table[MAXA], ans[MAXM];
Q queries[MAXM];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    sq = sqrt(n);
    for(int i = 0; i < n; i++) cin >> arr[i];
    cin >> m;
    for(int i = 0; i < m; i++) {
        cin >> queries[i].s >> queries[i].e;
        queries[i].s--; queries[i].e--;
        queries[i].i = i;
    }

    sort(queries, queries + m);

    int cnt = 0, s = queries[0].s, e = queries[0].e;
    for(int i = s; i <= e; i++) {
        if(++table[arr[i]] == 1) cnt++;
    }
    ans[queries[0].i] = cnt;

    for(int i = 1; i < m; i++) {
        auto [idx, s1, e1] = queries[i];
        while(s < s1) {
            if(--table[arr[s++]] == 0) cnt--;
        }
        while(s1 < s) {
            if(++table[arr[--s]] == 1) cnt++;
        }
        while(e < e1) {
            if(++table[arr[++e]] == 1) cnt++;
        }
        while(e1 < e) {
            if(--table[arr[e--]] == 0) cnt--;
        }
        ans[idx] = cnt;
    }

    for(int i = 0; i < m; i++) cout << ans[i] << "\n";
}