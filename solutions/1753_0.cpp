#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

const int INF = 987654321;

int v, e;
int start_point;
//dst, w;
vector<pair<int, int>> costs[200000];
int dists[20000];

void ShortestDist(int start) {
    //queue<pair<int, int>> que;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> que;
    dists[start] = 0;
    que.push({0, start});

    while(!que.empty()) {
        int dist = que.top().first;
        int cur = que.top().second; 
        que.pop();
        for(int i=0; i<costs[cur].size(); i++) {
            int dst = costs[cur][i].first;
            if(dists[dst] > dist + costs[cur][i].second) {
                dists[dst] = dist + costs[cur][i].second;
                que.push({dists[dst], dst});
            }
        }
    }
}

int main() {
    cin>>v>>e;
    cin>>start_point;

    for(int i=0; i<v; i++) {
        dists[i] = INF;
    }

    for(int i=0; i<e; i++) {
        int start;
        int end;
        int cost;

        cin>>start>>end>>cost;

        costs[start-1].push_back({end-1, cost});
    }

    ShortestDist(start_point-1);

    for(int i=0; i<v; i++) {
        if(dists[i] == INF)
            cout<<"INF\n";
        else
            cout<<dists[i]<<"\n";
    }
}