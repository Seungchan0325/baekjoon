#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 1010101;

int N, A[MAXN];

int solve(vector<int> v)
{
    int n = v.size();
    int ans = 0;
    priority_queue<int> pq;
    for(auto i : v) {
        if(pq.empty() || pq.top() <= i) {
            pq.push(i);
        } else {
            ans += pq.top() - i;
            pq.pop();
            pq.push(i);
            pq.push(i);
        }
    }
    return ans;
}

signed main()
{
    cin >> N;
    vector<int> v(N);
    for(auto&i:v) cin >> i;
    for(int i = 0; i < N; i++) v[i] -= i;
    int ans = solve(v);
    cout << ans;
}