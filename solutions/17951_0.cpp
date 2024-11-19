#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int N, K, A[MAXN];

bool chk(int t)
{
    int groups = 0;
    int s = 0;
    for(int i = 1; i <= N; i++) {
        if(s + A[i] >= t) {
            s = 0;
            groups++;
        } else {
            s += A[i];
        }
    }

    return groups >= K;
}

int main()
{
    cin >> N >> K;
    for(int i = 1; i <= N; i++) cin >> A[i];

    int lo = 0;
    int hi = 1e9;
    while(lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if(chk(mid)) lo = mid;
        else hi = mid;
    }
    cout << lo;
}