#include <bits/stdc++.h>

using namespace std;

using llint = long long;

const int MAXN = 100005;
const int MAXM = 100005;
const int MAXV = 1000005;

int sqrtN;

struct Q {
    int s, e, idx;
    bool operator < (const Q& x)
    {
        if(s/sqrtN != x.s/sqrtN) return s/sqrtN < x.s/sqrtN;
        return e < x.e;
    }
};

int N, M, K, arr[MAXN], cnt[1<<20];
llint ans[MAXM];
llint value;
Q queries[MAXM];

void push(int idx)
{
    value += cnt[arr[idx]^K];
    cnt[arr[idx]]++;
}

void pop(int idx)
{
    cnt[arr[idx]]--;
    value -= cnt[arr[idx]^K];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> K; sqrtN = sqrt(N);
    for(int i = 1; i <= N; i++) {
        cin >> arr[i];
        arr[i] ^= arr[i-1];
    }

    cin >> M;
    for(int i = 0; i < M; i++) {
        cin >> queries[i].s >> queries[i].e;
        queries[i].s--;
        queries[i].idx = i;
    }
    sort(queries, queries + M);

    int s = 0;
    int e = -1;
    for(int i = 0; i < M; i++) {
        while(s < queries[i].s) pop(s++);
        while(queries[i].s < s) push(--s);
        while(e < queries[i].e) push(++e);
        while(queries[i].e < e) pop(e--);

        ans[queries[i].idx] = value;
    }

    for(int i = 0; i < M; i++) {
        cout << ans[i] << "\n";
    }
}