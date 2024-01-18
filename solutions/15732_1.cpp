#include <bits/stdc++.h>

using namespace std;

const int MAXK = 10005;

int n, k, d, a[MAXK], b[MAXK], c[MAXK];

bool decision(int mid) {
    long long sum = 0;
    for(int i=0; i<k; i++) {
        if(mid < a[i]) continue;
        sum += ((min(b[i], mid) - a[i]) /  c[i]) + 1;
    }
    return d <= sum;
}

int main() {
    cin >> n >> k >> d;
    for(int i = 0; i < k; i++)
        cin >> a[i] >> b[i] >> c[i];

    int lo = 1, hi = n;
    while(lo < hi) {
        int mid = (lo + hi) / 2;

        if(decision(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    cout<<lo;
}