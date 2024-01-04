#include <iostream>
#include <climits>
#include <memory.h>

using namespace std;

const int NEGINF = INT_MIN;

int n, l[21], j[21];
int cache[101][21];

int LargestPleasure(int health, int idx) {
    if(idx >= n) return 0;

    int& ret = cache[health][idx];
    if(ret != -1) return ret;

    ret = LargestPleasure(health, idx+1);

    if(health-l[idx] > 0)
        ret = max(LargestPleasure(health-l[idx], idx+1)+j[idx], ret);

    return ret;
}

int main() {
    memset(cache, -1, sizeof(cache));
    
    cin>>n;
    for(int i=0; i<n; i++)
        cin>>l[i];
    for(int i=0; i<n; i++)
        cin>>j[i];

    int result = LargestPleasure(100, 0);

    cout<<result<<endl;
}