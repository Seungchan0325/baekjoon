#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll n, k, q;
vector<int> que[2000];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n>>k>>q;
    ll sum = 0;
    ll min_q = 0;
    for(int i=1; i<=n; i++) {
        bool flag = true;
        for(int j=0; j<k; j++) {
            int inp; cin>>inp;
            int min_dist = (i <= inp) ? inp - i : n - i + inp;
            sum += min_dist;
            if(min_dist != 0) flag = false;
        }
        if(flag && i == 1) min_q++;
    }
    min_q += (sum + n-1) / n;

    //cout<<min_q<<"\n";
    bool is_possible = q >= min_q;
    cout<<(int)is_possible;
}