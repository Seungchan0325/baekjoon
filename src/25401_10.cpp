#include <iostream>
#include <cmath>

using namespace std;

const int INF = 987654321;

int n, ans, arr[500];

int measure_error(int init, int d) {
    int ret = 0, i, dd;
    for(i=0, dd=init; i<n; i++, dd+=d) {
        ret += (arr[i] == dd) ? 0 : 1;
    }
    return ret;
}

int main() {
    cin>>n;
    for(int i=0; i<n; i++) cin>>arr[i];

    ans = INF;
    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            int diff = arr[j] - arr[i];
            int len = j - i + 1;
            if(diff % (len - 1) != 0) continue;
            int d = diff / (len - 1);
            int init = arr[i] + abs(i * d);
            ans = min(ans, measure_error(init, d));
        }
    }

    if(ans == INF) {
        ans = n-1;
    }

    cout<<ans<<"\n";
}