#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <assert.h>

using namespace std;

using ll = long long;

const ll INF = 1e9;

//[st en) 구간
ll pSumQuery(vector<ll>& pSum, int st, int en) {
    return pSum[en] - pSum[st];
}

ll solve(vector<ll>& road, vector<ll>& p) {
    ll ret = 0;

    road.push_back(INF); road.push_back(-INF);
    sort(road.begin(), road.end());
    sort(p.begin(), p.end());

    ll n = road.size();
    ll k = p.size();

    vector<ll> pSum(k+1, 0);
    for(int i=1; i<=k; i++) pSum[i] = pSum[i-1] + p[i-1];

    for(int i=0; i<k; i++) ret += pSumQuery(pSum, i, k) - p[i] * (k - i);
    
    int from = 0, to;
    for(int i=1; i<n; i++) {
        to = lower_bound(p.begin(), p.end(), road[i]) - p.begin();

        // printf("from: %lld\tto: %lld\n", from, to);
        // for(int j=from; j<to; j++) {
        //     int mid = upper_bound(p.begin(), p.end(), road[i-1] + road[i] - p[j]) - p.begin();
        //     mid = max(mid, j);
        //     printf("%lld %lld\n", 2 * (pSumQuery(pSum, j+1, mid) - road[i-1] * (mid - j + 1)), 2 * (road[i] * (to - mid) - pSumQuery(pSum, mid, to)));
        //     ret += 2 * (pSumQuery(pSum, min(j + 1, mid), mid) - road[i-1] * (mid - j + 1));
        //     ret += 2 * (road[i] * (to - mid) - pSumQuery(pSum, mid, to));
        // }
        // for(int j=from; j<to; j++) {
        //     int mid = upper_bound(p.begin(), p.end(), road[i-1] + road[i] - p[j]) - p.begin();
        //     mid = max(mid, j);
        //     for(int k=j+1; k<mid; k++) {
        //         printf("%d %d %d", j, k, (p[k] - road[i-1])*2);
        //         ret += 2 * (p[k] - road[i-1]);
        //     }
        //     for(int k=mid; k<to; k++) {
        //         ret += 2 * (road[i] - p[k]);
        //     }
        // }
        for(int j=from; j<to; j++) {
            for(int k=j+1; k<to; k++) {
                ret += 2 * min(road[i] - p[k], p[j] - road[i-1]);
            }
        }
        from = to;
        while(from < k && p[from] <= road[i]) from++;
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    ll n, m, k;
    cin>>n>>m>>k;
    vector<ll> road_x(n), road_y(m), p(k), q(k);
    for(auto& i : road_x) cin>>i;
    for(auto& i : road_y) cin>>i;
    for(int i=0; i<k; i++) cin>>p[i]>>q[i];

    ll ans = solve(road_x, p) + solve(road_y, q);
    cout<<ans;
}