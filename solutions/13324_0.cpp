#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 1010101;

int N, A[MAXN];

vector<int> solve(vector<int> v)
{
    int n = v.size();
    vector<int> B(n);
    priority_queue<int> pq;
    for(int i = 0; i < n; i++) {
        pq.push(v[i]);
        B[i] = pq.top();
        if(pq.top() > v[i]) {
            pq.pop();
            pq.push(v[i]);
        }
    }
    for(int i = n-1; i > 0; i--) B[i-1] = min(B[i-1], B[i]);
    return B;
}

signed main()
{
    cin >> N;
    vector<int> v(N);
    for(auto&i:v) cin >> i;
    for(int i = 0; i < N; i++) v[i] -= i;
    auto ans = solve(v);
    for(int i = 0; i < N; i++) cout << ans[i] + i << "\n";
}