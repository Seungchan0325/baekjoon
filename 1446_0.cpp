#include <iostream>
#include <algorithm>

using namespace std;

struct road {
    int start;
    int end;
    int distance;
};

const int INF = 987654321;

int n, d;
road roads[12];

int GetShortestDistance(int start) {
    int ret = d-start;
    for(int i=0; i<n; i++) {
        if(roads[i].start >= start && roads[i].end <= d) {
            int distance = roads[i].distance + (roads[i].start - start);
            ret = min(GetShortestDistance(roads[i].end) + distance, ret);
        }
    }
    return ret;
}

int main() {
    cin>>n>>d;
    for(int i=0; i<n; i++) {
        cin>>roads[i].start>>roads[i].end>>roads[i].distance;
    }

    sort(roads, roads+n, 
    [](const road& a, const road& b){
        if(a.start < b.start)
            return true;
        else
            return false;
    });

    int result = GetShortestDistance(0);
    cout<<result;
}