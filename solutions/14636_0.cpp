#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll n, m;
vector<pair<ll, ll>> seller, buyer;

ll DnC(ll s, ll e, ll optL, ll optR)
{
    if(e < s) return -1e18;

    ll m = (s + e) / 2;
    ll opt = -1e18;
    ll optI = 0;
    for(ll i = optL; i <= optR && seller[i].first < buyer[m].first; i++) {
        auto [d, p] = seller[i];
        auto [e, q] = buyer[m];
        ll cand = (e - d) * (q - p);
        if(cand > opt) {
            opt = cand;
            optI = i;
        }
    }

    opt = max(opt, DnC(s, m-1, optL, optI));
    opt = max(opt, DnC(m+1, e, optI, optR));
    return opt;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> m;
    seller.resize(n);
    buyer.resize(m);
    for(auto& [d, p] : seller) cin >> p >> d;
    for(auto& [e, q] : buyer) cin >> q >> e;
    sort(seller.begin(), seller.end());
    sort(buyer.begin(), buyer.end());

    vector<pair<ll, ll>> tmp;
    for(auto& [d, p] : seller) {
        if(tmp.empty() || p < tmp.back().second) tmp.emplace_back(d, p);
    }
    seller = tmp;

    reverse(buyer.begin(), buyer.end());
    tmp.clear();
    for(auto& [e, q] : buyer) {
        if(tmp.empty() || q > tmp.back().second) tmp.emplace_back(e, q);
    }
    buyer = tmp;
    reverse(buyer.begin(), buyer.end());

    ll result = DnC(0, buyer.size()-1, 0, seller.size()-1);
    cout << max(result, 0LL);
}