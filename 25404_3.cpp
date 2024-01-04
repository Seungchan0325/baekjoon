#include <iostream>
#include <algorithm>
#include <utility>
#include <cmath>

using namespace std;

using pii = pair<int, int>;

int n, a[100000];
pii sa[100000];

int calc_cost(int i, int j) {
    if(j < i) swap(i, j);
    return min(j-i, n-j+i);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>n;
    for(int i=0; i<n; i++) {
        cin>>a[i];
        sa[i] = {a[i], i};
    }
    sort(sa, sa+n);

    int cur = 0, ans = 0;
    for(int i=0; i<n; i++) {
        ans += calc_cost(cur, sa[i].second);
        cur = sa[i].second;
    }
    cout<<ans<<"\n";
}