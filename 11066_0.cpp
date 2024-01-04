#include <iostream>
#include <memory.h>

using namespace std;

const int INF = 987654321;

int k, files[500], psum[501];
int cache[500][500];

int SmallestCost(int start, int end) {
    if(start == end) return 0;
    if(start+1 == end) return files[start] + files[end];
    
    int& ret = cache[start][end];
    if(ret != -1) return ret;

    ret = INF;
    for(int mid=start; mid<end; mid++) {
        ret = min(SmallestCost(start, mid) + SmallestCost(mid+1, end) + (psum[end+1] - psum[start]), ret);
    }

    return ret;
}

int main() {
    int tc;
    cin>>tc;
    while(tc--) {
        memset(cache, -1, sizeof(cache));
        cin>>k;
        for(int i=0; i<k; i++) {
            cin>>files[i];
            psum[i+1] = psum[i] + files[i];
        }

        int result = SmallestCost(0, k-1);

        cout<<result<<endl;
    }
}