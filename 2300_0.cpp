#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

const int INF = 987654321;
const int MAXN = 10005;

int n, cache[MAXN];
pii dots[MAXN];

int minCost(int left) {
    if(left == n) return 0;

    int& ret = cache[left];
    if(ret != -1) return ret;

    ret = INF;
    int side = -1;
    for(int right = left; right < n;) {
        side = max(2 * abs(dots[right].second), side);
        side = max(dots[right].first - dots[left].first, side);

        while(right < n && dots[right].first - dots[left].first <= side && 2 * abs(dots[right].second) <= side) right++;
        ret = min(minCost(right) + side, ret);
    }

    return ret;
}

int main() {
    cin>>n;
    for(int i=0; i<n; i++) cin>>dots[i].first>>dots[i].second;
    sort(dots, dots + n);

    memset(cache, -1, sizeof(cache));
    int result = minCost(0);
    cout<<result;
}