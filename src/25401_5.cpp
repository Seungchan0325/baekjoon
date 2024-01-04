#include <iostream>
#include <cmath>

using namespace std;

const int INF = 987654321;

int n, ans, arr[500];

int measure_error(int init, int d) {
    int ret = 0, i, dd;
    for(i=0, dd=init; i<n && ret < ans; i++, dd+=d) {
        //printf("%d ", dd);
        ret += (arr[i] == dd) ? 0 : 1;
        //if(ret >= ans) return ret;
    }
    //printf("\nerror: %d\n", ret);
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin>>n;
    for(int i=0; i<n; i++) cin>>arr[i];

    ans = INF;
    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            //putchar('\n');
            int diff = arr[j] - arr[i];
            int len = j - i + 1;
            //printf("i: %d, j: %d\n", i+1, j+1);
            //printf("diff: %d\tlen: %d\tdiff % (len - 1): %d\tdelta : %d\n", diff, len, diff % (len - 1), diff / (len - 1));
            if(diff % (len - 1) != 0) continue;
            int d = diff / (len - 1);
            int init = arr[i] - i * d;
            ans = min(ans, measure_error(init, d));
        }
    }

    if(ans == INF) {
        ans = n-1;
    }

    cout<<ans<<"\n";
}