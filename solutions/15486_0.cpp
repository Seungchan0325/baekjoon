#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int MAXN = 1500005;

int n, t[MAXN], p[MAXN], cache[MAXN];

int f(int day) {
    if(day == n) return 0;
    if(day > n) return -INF;

    int& ret = cache[day];
    if(ret != -1) return ret;

    ret = max(f(day + t[day]) + p[day], f(day + 1));

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n;
    for(int i=0; i<n; i++) cin>>t[i]>>p[i];

    memset(cache, -1, sizeof(cache));
    int result = f(0);

    cout<<result;
}