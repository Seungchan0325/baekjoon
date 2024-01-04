#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100001;

long long m, n, l;
long long ms[MAXN], a[MAXN], b[MAXN];

int main() {
    cin>>m>>n>>l;
    for(int i=0; i<m; i++) cin>>ms[i];
    for(int i=0; i<n; i++) cin>>a[i]>>b[i];

    sort(ms, ms + m);

    int cnt = 0;
    for(int i=0; i<n; i++) {
        int hi = upper_bound(ms, ms + m, a[i]) - ms;
        int lo = hi - 1;

        if(ms[hi] - a[i] + b[i] <= l || (0 <= lo && a[i] - ms[lo] + b[i] <= l)) {
            cnt++;
        }
    }
    cout<<cnt;
}