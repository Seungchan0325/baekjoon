#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits.h>

using namespace std;

using ll = long long int;

int main() {
    int n;
    cin >> n;
    vector<ll> v(n);

    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }

    sort(v.begin(), v.end());

    ll minval = LONG_LONG_MAX;
    int ans[3];
    int& ans1 = ans[0], & ans2 = ans[1], & ans3 = ans[2];

    for(int i = 0; i < n; i++) {
        int start = 0,
        end = v.size() - 1;
    
        while(start < end) {
            if(start == i) {
                start++;
                continue;
            }
            if(end == i) {
                end--;
                continue;
            }

            ll a = v[start] + v[end] + v[i];
            if(abs(a) < minval) {
                ans1 = v[i];
                ans2 = v[start];
                ans3 = v[end];
                minval = abs(a);
            }
            if(a < 0){
                start++;
            }else if(a > 0){
                end--;
            }else{
                ans1 = v[i];
                ans2 = v[start];
                ans3 = v[end];
                break;
            }
        }
    }
    sort(ans, ans + 3);
    cout << ans1 << " " << ans2 << " " << ans3 << endl;
}