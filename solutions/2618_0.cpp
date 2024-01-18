#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;
const int INF = 987654321;

int n, w, ax[MAXN+2], ay[MAXN+2], cache[MAXN];

int distance(int i, int j) {
    return abs(ax[i] - ax[j]) + abs(ay[i] - ay[j]);
}

int minDist(int idx) {
    if(idx == w) return 0;

    int& ret = cache[idx];
    if(ret != -1) return ret;

    ret = INF;
    int dist = 0;
    for(int next=idx+1; next<=w; next++) {
        int next_dist = minDist(next) + dist + distance(idx-1, next);
        dist += distance(next-1, next);
        ret = min(next_dist, ret);
    }
    ret = min(dist, ret);

    return ret;
}

void restructure(int idx, int ans, int p) {
    if(idx == w) cout<<p+1<<"\n";
    int dist = 0;
    for(int next=idx+1; next<=w; next++) {
        int next_dist = minDist(next) + dist + distance(idx-1, next);
        if(next_dist == ans) {
            for(int i=idx; i<next; i++)
                cout<<p+1<<"\n";
            restructure(next, minDist(next), p^1);
            return;
        }
        dist += distance(next-1, next);
    }

    for(int i=idx; i<=w; i++)
        cout<<p+1<<"\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin>>n;
    cin>>w;
    for(int i=1; i<=w; i++) cin>>ax[i]>>ay[i];
    ax[MAXN] = ay[MAXN] = 1;
    ax[MAXN+1] = ay[MAXN+1] = n;

    memset(cache, -1, sizeof(cache));

    int ans = INF;
    int dist = 0;
    int p1 = distance(MAXN, 1), p2 = distance(MAXN+1, 1);
    for(int i=2; i<=w; i++) {
        int min_dist = p1 + dist + minDist(i) + distance(MAXN+1, i);
        ans = min(min_dist, ans);
        
        min_dist = p2 + dist + minDist(i) + distance(MAXN, i);
        ans = min(min_dist, ans);
        
        dist += distance(i-1, i);
    }
    ans = min(p1 + dist, ans);
    ans = min(p2 + dist, ans);

    cout<<ans<<"\n";
    dist = 0;
    for(int i=2; i<=w; i++) {
        int min_dist = p1 + dist + minDist(i) + distance(MAXN+1, i);
        if(min_dist == ans) {
            for(int j=1; j<i; j++)
                cout<<"1\n";
            restructure(i, minDist(i), 1);
            return 0;
        }
        
        min_dist = p2 + dist + minDist(i) + distance(MAXN, i);
        if(min_dist == ans) {
            for(int j=1; j<i; j++)
                cout<<"2\n";
            restructure(i, minDist(i), 0);
            return 0;
        }
        
        dist += distance(i-1, i);
    }
    if(p1 + dist == ans) {
        for(int i=1; i<=w; i++)
            cout<<"1\n";
    }
    if(p2 + dist == ans) {
        for(int i=1; i<=w; i++)
            cout<<"2\n";
    }
}