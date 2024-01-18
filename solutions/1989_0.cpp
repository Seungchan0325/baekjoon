#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll n, arr[1000005];

pair<ll, pair<int, int>> Choice(ll left, ll right) {
    if(left == right) return {arr[left] * arr[left], make_pair(left, left)};

    pair<ll, pair<int, int>> ret(-1, {-1, -1});
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
        ret = max({sum * min_v, make_pair(lo, hi)}, ret);
    }

    return ret;
}

int main() {
    cin >> n;
    for(ll i = 0; i < n; i++) cin >> arr[i];
    pair<ll, pair<int, int>> result = Choice(0, n-1);
    cout << result.first << "\n";
    cout << result.second.first+1 << " " << result.second.second+1;
}