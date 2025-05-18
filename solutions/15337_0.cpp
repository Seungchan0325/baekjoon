#include <bits/stdc++.h>

using namespace std;

const int MAXN = 202020;

int n, a[MAXN], b[MAXN];

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i] >> b[i];
    vector<int> v(n);
    iota(v.begin(), v.end(), 1);
    sort(v.begin(), v.end(), [](int i, int j){
        if(a[i] != a[j]) return a[i] < a[j];
        return b[i] < b[j];
    });
    priority_queue<int> pq;
    int ans1 = 0, ans2 = 0;
    for(auto i : v) {
        while(pq.size() && -pq.top() <= a[i]) pq.pop();
        pq.push(-b[i]);
        ans1 = max<int>(ans1, pq.size());
    }
    while(pq.size()) pq.pop();
    int idx = 0;
    for(auto i : v) {
        while(idx < n && a[v[idx]] < b[i]) pq.push(-b[v[idx++]]);
        while(pq.size() && -pq.top() <= a[i]) pq.pop();
        ans2 = max<int>(ans2, pq.size());
    }
    cout << ans2 << " " << ans1;
}