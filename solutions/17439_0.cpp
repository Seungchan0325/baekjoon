#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 50505;

ll N, K, s[MAXN], dp[MAXN], comp[MAXN];

ll C(int i, int j)
{
    return (i - j) * (s[i] - s[j]);
}

int cross(int i, int j)
{
    int lo = 1;
    int hi = N+1;
    while(lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if(dp[i] + C(i, mid) < dp[j] + C(j, mid)) lo = mid;
        else hi = mid;
    }
    return hi;
}

void run(ll lambda)
{
    deque<int> q;
    q.emplace_back(0);
    for(int i = 1; i <= N; i++) {
        while(q.size() >= 2 && cross(q[0], q[1]) <= i) q.pop_front();
        dp[i] = dp[q[0]] + C(i, q[0]) + lambda;
        comp[i] = comp[q[0]] + 1;
        while(q.size() >= 2 && cross(q.end()[-2], q.end()[-1]) >= cross(q.end()[-1], i)) q.pop_back();
        q.push_back(i);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> K;
    for(int i = 1; i <= N; i++) {
        cin >> s[i];
        s[i] += s[i-1];
    }

    ll lo = -1;
    ll hi = 1e15;
    while(lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        run(mid);
        if(comp[N] > K) lo = mid;
        else hi = mid;
    }
    run(hi);
    cout << dp[N] - hi * comp[N] << "\n";
}