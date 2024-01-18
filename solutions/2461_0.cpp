#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define INF 987654321

int N, M;
vector<int> v[1000];
priority_queue<pair<int, pair<int, int>>> pq;

int main() {
    cin>>N>>M;
    for(int i=0; i<N; i++) {
        v[i].resize(M);
        for(auto& j : v[i])
            cin>>j;
    }

    int result=INF;
    int minNum=INF;
    
    for(int i=0; i<N; i++) {
        sort(v[i].begin(), v[i].end(), greater<int>());
        minNum = min(v[i][0], minNum);
        pq.push({v[i][0], {i, 0}});
    }

    while(!pq.empty()) {
        auto top=pq.top(); pq.pop();

        result = min(top.first-minNum, result);

        if(top.second.second+1 == M) break;

        minNum = min(v[top.second.first][top.second.second+1], minNum);
        pq.push({v[top.second.first][top.second.second+1], {top.second.first, top.second.second+1}});
    }
    cout<<result;
}