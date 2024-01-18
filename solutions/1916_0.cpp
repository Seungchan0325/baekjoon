#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>

using namespace std;
using pii = pair<int, int>;

const int INF = 987654321;

int N, M;
int SRC, DST;
//cost, dst
vector<pii> costs[1001];

int GetSmallestCost(int src, int dst) {
    int dists[1001];
    //cost, src
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    
    for(int i=0; i<N; i++) {
        dists[i] = INF;
    }
    dists[src] = 0;
    pq.push({0, src});

    while(!pq.empty()) {
        auto top = pq.top(); pq.pop();
        int start = top.second;
        int cost = top.first;
        for(auto& i : costs[start]) {
            if(dists[i.second] > i.first + cost) {
                dists[i.second] = i.first + cost;
                pq.push({dists[i.second], i.second});
            }
        }
    }

    return dists[dst];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //cout.tie(NULL);

    cin>>N>>M;
    for(int i=0; i<M; i++) {
        int src, dst, cost;
        cin>>src>>dst>>cost;
        src--; dst--;
        costs[src].push_back({cost, dst});
    }
    for(int i=0; i<N; i++) {
        sort(costs[i].begin(), costs[i].end());
    }
    cin>>SRC>>DST;
    SRC--; DST--;
    
    int result = GetSmallestCost(SRC, DST);

    cout<<result<<"\n";
}