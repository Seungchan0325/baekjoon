#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<ll, ll>;

const int MAXN = 200005;

int N, Q;
pii arr[MAXN];
ll leftx[MAXN], rightx[MAXN], lefta[MAXN], righta[MAXN];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> Q;
    for(int i = 0; i < N; i++)
        cin >> arr[i].second >> arr[i].first;
    
    sort(arr, arr + N);

    leftx[0] = 0;
    lefta[0] = arr[0].second;
    for(int i = 1; i < N; i++) {
        leftx[i] = lefta[i-1] * (arr[i].first - arr[i-1].first) + leftx[i-1];
        lefta[i] = lefta[i-1] + arr[i].second;
    }

    rightx[N-1] = 0;
    righta[N-1] = arr[N-1].second;
    for(int i = N-2; i >= 0; i--) {
        rightx[i] = righta[i+1] * (arr[i+1].first - arr[i].first) + rightx[i+1];
        righta[i] = righta[i+1] + arr[i].second;
    }

    int x;
    while(Q--) {
        cin >> x;

        int idx = upper_bound(arr, arr + N, make_pair((ll)x, 0LL)) - arr;

        ll ans = 0;
        if(idx < N)
            ans += rightx[idx] + righta[idx] * (arr[idx].first - x);
        idx--;
        if(0 <= idx)
            ans += leftx[idx] + lefta[idx] * (x - arr[idx].first);
        
        cout << ans << "\n";
    }
}