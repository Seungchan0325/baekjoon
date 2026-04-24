#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 505050;

char state[MAXN];
ll N, L[MAXN], R[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i <= 2*N; i++) cin >> L[i] >> R[i];

    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<>> unl, unr, lmr, rml;
    for(int i = 1; i <= 2*N; i++) {
        unl.push({L[i], i});
        unr.push({R[i], i});
    }

    ll ans = 0;
    for(int i = 1; i <= N; i++) {
        while(unl.size() && state[unl.top().second] != 0) unl.pop();
        while(unr.size() && state[unr.top().second] != 0) unr.pop();
        while(rml.size() && state[rml.top().second] != 1) rml.pop();
        while(lmr.size() && state[lmr.top().second] != 2) lmr.pop();
        ll l1 = unl.size() ? unl.top().first : 1e18;
        ll l2 = lmr.size() && unr.size() ? lmr.top().first + unr.top().first : 1e18;
        if(l1 < l2) {
            ans += l1;
            int j = unl.top().second; unl.pop();
            state[j] = 1;
            rml.push({R[j]-L[j], j});
        } else {
            ans += l2;
            int j = lmr.top().second; lmr.pop();
            int k = unr.top().second; unr.pop();
            state[j] = 1;
            state[k] = 2;
            rml.push({R[j]-L[j], j});
            lmr.push({L[k]-R[k], k});
        }
        while(unl.size() && state[unl.top().second] != 0) unl.pop();
        while(unr.size() && state[unr.top().second] != 0) unr.pop();
        while(rml.size() && state[rml.top().second] != 1) rml.pop();
        while(lmr.size() && state[lmr.top().second] != 2) lmr.pop();
        ll r1 = unr.size() ? unr.top().first : 1e18;
        ll r2 = rml.size() && unl.size() ? rml.top().first + unl.top().first : 1e18;
        if(r1 < r2) {
            ans += r1;
            int j = unr.top().second; unr.pop();
            state[j] = 2;
            lmr.push({L[j]-R[j], j});
        } else {
            ans += r2;
            int j = rml.top().second; rml.pop();
            int k = unl.top().second; unl.pop();
            state[j] = 2;
            state[k] = 1;
            lmr.push({L[j]-R[j], j});
            rml.push({R[k]-L[k], k});
        }
        cout << ans << "\n";
    }
}
