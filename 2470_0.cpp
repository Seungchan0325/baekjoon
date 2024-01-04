#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

using ll = long long int;

int main() {
    ll n;
    cin >> n;
    vector<ll> v(n);

    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }

    sort(v.begin(), v.end());

    ll minval = 2000000000;
    pair<ll, ll> ans;
    int start = 0,
        end   = v.size() - 1;
    
    while(start < end) {
        ll a = v[start] + v[end];
        if(abs(a) < minval) {
            ans = pair(v[start], v[end]);
            minval = abs(a);
        }
        if(a < 0){
            start++;
        }else if(a > 0){
            end--;
        }else{
            ans = pair(v[start], v[end]);
            break;
        }
    }
    cout << ans.first << " " << ans.second << "\n";
}