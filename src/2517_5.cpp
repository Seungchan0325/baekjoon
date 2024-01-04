#include <iostream>
#include <algorithm>

using namespace std;
using pii = pair<int, int>;

int n, arr[500000], fenwick[500001] = {0};

void update(int idx, int value) {
    while(idx < n) {
        fenwick[idx] += value;
        idx += (idx & -idx);
    }
}

int sum(int idx) {
    int ret = 0;
    while(idx > 0) {
        ret += fenwick[idx];
        idx -= (idx & -idx);
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin>>n;
    for(int i=0; i<n; i++) {
        cin>>arr[i];
    }

    {   //Coordination compression
        int tmp[500000];
        for(int i=0; i<n; i++)
            tmp[i] = arr[i];
        sort(tmp, tmp+n);
        for(int i=0; i<n; i++)
            arr[i] = lower_bound(tmp, tmp+n, arr[i]) - tmp + 1;
    }

    int ans, runners=0;
    for(int i=0; i<n; i++) {
        ans = runners - sum(arr[i]-1);
        update(arr[i], 1);
        runners++;
        cout<<ans+1<<"\n";
    }
}