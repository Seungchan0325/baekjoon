#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;

int n, w[17][17], cache[17][1<<17];

int tsp(int here, int visited) {
    if(visited == (1<<n)-1) return w[here][0];

    int& ret = cache[here][visited];
    if(ret != -1) return ret;

    ret = INF;
    for(int next = 0; next < n; next++) {
        if(visited & (1<<next)) continue;
        int cand = w[here][next] + tsp(next, visited + (1<<next));
        ret = min(cand, ret);
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++) {
            cin>>w[i][j];
            if(w[i][j] == 0) w[i][j] = INF;
        }
    
    memset(cache, -1, sizeof(cache));
    int result = tsp(0, 1);
    cout<<result;
}