#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000005;
const int MAXQ = 1000005;

int sqrtN;

struct Qt {
    int s, e, idx;
    bool operator < (const Qt& x)
    {
        if(s / sqrtN != x.s / sqrtN) return s / sqrtN < x.s / sqrtN;
        return e < x.e;
    }
};

int N, Q, arr[MAXN], cnt[MAXN], ans[MAXQ];
Qt queries[MAXQ];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N; sqrtN = sqrt(N);
    for(int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    vector<int> v(arr, arr + N);
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for(int i = 0; i < N; i++) {
        arr[i] = lower_bound(v.begin(), v.end(), arr[i]) - v.begin();
    }

    cin >> Q;
    for(int i = 0; i < Q; i++) {
        cin >> queries[i].s >> queries[i].e;
        queries[i].s--; queries[i].e--;
        queries[i].idx = i;
    }
    sort(queries, queries + Q);

    int s = queries[0].s;
    int e = queries[0].s - 1;
    int diff = 0;
    for(int i = 0; i < Q; i++) {
        while(s < queries[i].s) if(--cnt[arr[s++]] == 0) diff--;
        while(queries[i].s < s) if(++cnt[arr[--s]] == 1) diff++;
        while(e < queries[i].e) if(++cnt[arr[++e]] == 1) diff++;
        while(queries[i].e < e) if(--cnt[arr[e--]] == 0) diff--;
        ans[queries[i].idx] = diff;
    }

    for(int i = 0; i < Q; i++) {
        cout << ans[i] << "\n";
    }
}