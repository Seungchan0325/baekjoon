#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int MAXN = 200005;

int dist[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    memset(dist, 0x7F, sizeof(dist));

    deque<int> q;
    q.push_front(n);
    dist[n] = 0;
    while(!q.empty()) {
        int cur = q.front(); q.pop_front();

        if(2 * cur < MAXN && dist[cur] < dist[2 * cur]) {
            dist[2 * cur] = dist[cur];
            q.push_front(2 * cur);
        }
        if(0 <= cur - 1 && dist[cur] + 1 < dist[cur - 1]) {
            dist[cur - 1] = dist[cur] + 1;
            q.push_back(cur - 1);
        }
        if(cur + 1 < MAXN && dist[cur] + 1 < dist[cur + 1]) {
            dist[cur + 1] = dist[cur] + 1;
            q.push_back(cur + 1);
        }
    }

    cout << dist[k];
}