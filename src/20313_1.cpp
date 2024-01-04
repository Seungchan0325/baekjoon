#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using ii = pair<long long, long long>;
using iii = pair<ii, int>;
#define INF 1e17
vector<ii> v[101][1001];
long long list[2001][3] = {0, };
long long d[101][1001];
long long n, k;
void dij(long long s) {
	d[0][s] = 0;
	priority_queue<iii, vector<iii>, greater<iii>> pq;
	pq.push({{0, s}, 0});
	while(!pq.empty()) {
		long long dis = pq.top().first.first;
		int now = pq.top().first.second;
		int layer = pq.top().second;
		pq.pop();
		if(d[layer][now] < dis) continue;
		for(int i = layer; i <= k; i++) {
			for(ii nxt : v[i][now]) {
				long long dnxt = dis+nxt.second;
				if(dnxt < d[i][nxt.first]) {
					d[i][nxt.first] = dnxt;
					pq.push({{dnxt, nxt.first}, i});
				}
			}
		}
	}
}
int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
	long long m, s, f;
	cin >> n >> m >> s >> f;
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < 3; j++) {
			cin >> list[i][j];
		}
		v[0][list[i][0]].push_back({list[i][1], list[i][2]});
		v[0][list[i][1]].push_back({list[i][0], list[i][2]});
	}
	cin >> k;
	for(int i = 1; i <= k; i++) {
		for(int j = 0; j < m; j++) {
      int a;
      cin >> a;
			v[i][list[j][0]].push_back({list[j][1], a});	
      v[i][list[j][1]].push_back({list[j][0], a});
		}
	}
  for(int i = 1; i <= n; i++) {
    for(int j = 0; j <= k; j++) {
			d[j][i] = INF;
		}
  }
  dij(s);
	long long ans = INF;
	for(int i = 0; i <= k; i++) {
		ans = min(ans, d[i][f]);
	}
	cout << ans;
}