#include <bits/stdc++.h>

using namespace std;

const long long MAXN = 100005;

long long n, t[MAXN];

// [start, end]
long long GetMaxWage(long long start, long long end) {
    if(start == end) return t[start];
    
    long long mid = (start + end) / 2;
    long long ret = max(GetMaxWage(start, mid), GetMaxWage(mid + 1, end));

    long long lo, hi, wage;
    lo = hi = mid;
    wage = t[mid];
    while(start <= lo && hi <= end) {
        if(end < hi || (start <= lo && t[lo - 1] >= t[hi + 1])) {
            lo--;
            wage = min(t[lo], wage);
        } else {
            hi++;
            wage = min(t[hi], wage);
        }
        ret = max((hi - lo + 1) * wage, ret);
    }

    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n;
    for(long long i = 0; i < n; i++) {
        cin >> t[i];
    }

    long long result = GetMaxWage(0, n - 1);
    cout << result;
}