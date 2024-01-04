#include <iostream>
#include <memory.h>

using namespace std;

int n, t, point[101], study_time[101];
int cache[101][10001];

int LargestPoint(int unit, int time) {
    if(unit == n || time == 0) return 0;

    int& ret = cache[unit][time];
    if(ret != -1) return ret;

    ret = max(LargestPoint(unit+1, time), ret);
    if(0 <= time-study_time[unit])
        ret = max(LargestPoint(unit+1, time-study_time[unit])+point[unit], ret);
    
    return ret;
}

int main() {
    memset(cache, -1, sizeof(cache));

    cin>>n>>t;
    for(int i=0; i<n; i++) {
        cin>>study_time[i]>>point[i];
    }

    int result = LargestPoint(0, t);

    cout<<result<<endl;
}