#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MAXN = 1005;
const ll MAXM = 205;

ll m, n;
pair<ll, ll> src[MAXM], dst[MAXN];

int main()
{
    cin >> m;
    for(ll i = 0; i < m; i++) {
        cin >> src[i].first >> src[i].second;
    }
    cin >> n;
    for(ll i = 0; i < n; i++) {
        cin >> dst[i].first >> dst[i].second;
    }

    sort(dst, dst + n);
    for(ll i = 0; i < m; i++) {
        for(ll j = 0; j < n; j++) {
            ll dx = dst[j].first - src[i].first;
            ll dy = dst[j].second - src[i].second;
            bool is_possible = true;
            for(ll k = 0; k < m; k++) {
                ll nx = src[k].first + dx;
                ll ny = src[k].second + dy;
                if(!binary_search(dst, dst + n, make_pair(nx, ny))) {
                    is_possible = false;
                    break;
                }
            }
            if(is_possible) {
                cout << dx << " " << dy << "\n";
                return 0;
            }
        }
    }
}