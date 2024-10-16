#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int N, K, A[MAXN], B[MAXN];
long long ans;
int tree[MAXN];
pair<int, int> u[MAXN];

void upd(int x, int v)
{
    while(x <= N) {
        tree[x] += v;
        x += x & -x;
    }
}

int qry(int x)
{
    x = min(x, N);
    int ret = 0;
    while(x > 0) {
        ret += tree[x];
        x -= x & -x;
    }
    return ret;
}

void f(int s, int e)
{
    if(s == e) return;
    int m = (s + e) / 2;
    f(s, m);
    f(m+1, e);
    sort(u + s, u + m + 1);
    sort(u + m + 1, u + e + 1);
    int j = m+1;
    for(int i = s; i <= m; i++) {
        for(; j <= e && u[j].first < u[i].first; j++) upd(u[j].second, 1);
        ans += qry(N) - qry(u[i].second + K) + qry(u[i].second - K - 1);
    }
    for(int i = m+1; i < j; i++) upd(u[i].second, -1);
}

int main()
{
    cin >> N >> K;
    for(int i = 1; i <= N; i++) {
        int a; cin >> a;
        A[a] = i;
    }
    for(int i = 1; i <= N; i++) {
        int b; cin >> b;
        B[b] = i;
    }
    for(int i = 1; i <= N; i++) u[A[i]] = {B[i], i};
    f(1, N);

    cout << ans;
}