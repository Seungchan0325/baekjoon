#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 202020;
const ll inf = 1e18;

struct AB {
    ll a, b, acc;
    auto operator <=> (const AB& t) const {
        return (__int128)a * t.b - (__int128)t.a * b;
    }
};

ll n, a[MAXN];
vector<AB> pops[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    ll ans = 0;
    for(int i = 1; i <= n; i++) ans += (n-1) * a[i];
    vector<AB> vl = {{-inf, 1, 0}}, vr = {{-inf, 1, 0}};
    vector<ll> sl = {0}, sr = {0};
    vector<ll> nl = {0}, nr = {0};
    auto push = [&](vector<AB>& v, vector<ll>& s, vector<ll>& n,
                    vector<AB>& vv, vector<ll>& ss, vector<ll>& nn,
                    AB now) {
        int lo = 0;
        int hi = vv.size();
        while(lo+1<hi) {
            int mid = (lo+hi)/2;
            if(vv[mid] < now) lo = mid;
            else hi = mid;
        }
        ans += ss[lo] * now.b;
        ans += (nn.back()-nn[lo]) * now.a;
        ans += now.acc;
        ans += s.back() * now.b;
        v.push_back(now);
        s.push_back(s.back() + now.a);
        n.push_back(n.back() + now.b);
    };
    auto pop = [&](vector<AB>& v, vector<ll>& s, vector<ll>& n,
                   vector<AB>& vv, vector<ll>& ss, vector<ll>& nn) {
        AB now = v.back();
        v.pop_back();
        s.pop_back();
        n.pop_back();
        int lo = 0;
        int hi = vv.size();
        while(lo+1<hi) {
            int mid = (lo+hi)/2;
            if(vv[mid] < now) lo = mid;
            else hi = mid;
        }
        ans -= ss[lo] * now.b;
        ans -= (nn.back()-nn[lo]) * now.a;
        ans -= now.acc;
        ans -= s.back() * now.b;
    };

    for(int i = n; i >= 1; i--) {
        AB now = {-a[i], 1, 0};
        while(vl.size() && now <= vl.back()) {
            auto poped = vl.back();
            pop(vl, sl, nl, vr, sr, nr);
            pops[i].push_back(poped);
            now.acc += poped.acc + poped.a * now.b;
            now.a += poped.a;
            now.b += poped.b;
        }
        push(vl, sl, nl, vr, sr, nr, now);
    }

    for(int i = 1; i <= n; i++) {
        pop(vl, sl, nl, vr, sr, nr);
        while(pops[i].size()) {
            push(vl, sl, nl, vr, sr, nr, pops[i].back());
            pops[i].pop_back();
        }
        cout << ans << " ";

        AB now = {-a[i], 1, 0};
        while(vr.size() && now <= vr.back()) {
            auto poped = vr.back();
            pop(vr, sr, nr, vl, sl, nl);
            now.acc += poped.acc + poped.a * now.b;
            now.a += poped.a;
            now.b += poped.b;
        }
        push(vr, sr, nr, vl, sl, nl, now);
    }
}
