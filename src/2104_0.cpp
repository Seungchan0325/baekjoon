#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll n, arr[100005];

ll Choice(ll left, ll right) {
    if(left == right) return arr[left] * arr[left];

    ll ret = -1;
    ll mid = (left + right) / 2;
    ret = max(ret, Choice(left, mid));
    ret = max(ret, Choice(mid+1, right));

    ll lo, hi;
    ll sum, min_v;
    lo = hi = mid;
    sum = min_v = arr[lo];
    while(left < lo || hi < right) {
        if((left < lo && arr[hi+1] < arr[lo-1]) || !(hi < right)) {
            lo--;
            sum += arr[lo];
            min_v = min(arr[lo], min_v);
        } else {
            hi++;
            sum += arr[hi];
            min_v = min(arr[hi], min_v);
        }
        ret = max(sum * min_v, ret);
    }

    return ret;
}

int main() {
    cin >> n;
    for(ll i = 0; i < n; i++) cin >> arr[i];
    ll result = Choice(0, n-1);
    cout << result;
}