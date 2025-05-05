#include <bits/stdc++.h>

using namespace std;

using ll = __int128_t;

#define ssize(s) (ll)s.size()

const ll INF = 1e18;
const ll S1 = 1'000'000;

ll lcount(string s)
{
    s.push_back('#');
    for(ll i = 0; i < s.size(); i++) {
        if(s[i] != '0') return i;
    }
}

ll rcount(string s)
{
    reverse(s.begin(), s.end());
    return lcount(s);
}

ll compute(ll c, ll s1, ll mid, ll s2)
{
    c -= s1 + s2;
    return (c + mid - 1) / mid;
}
ll c;
void myexit(ll ans)
{
    if(ans+c > 1e16) cout << "-1";
    else cout << (long long)ans;
    exit(0);
}

int main()
{
    string s1, s2;
    cin >> s1 >> s2;
    long long _c; cin >> _c;
    c = _c;
    if(lcount(s1) >= c) myexit(0);
    if(lcount(s1) == s1.size() && lcount(s2) == s2.size()) myexit(0);
    vector<ll> cand;
    if(rcount(s1) + lcount(s1) >= c) cand.push_back(ssize(s1) - rcount(s1));
    if(c <= 50 && s1.find(string(c, '0')) != string::npos) cand.push_back(s1.find(string(c, '0')));
    if(c <= 50 && s2.find(string(c, '0')) != string::npos) cand.push_back(s1.size() * S1 + s2.find(string(c, '0')));
    if(lcount(s1) == s1.size())
    {
        ll a;
        a = compute(c, rcount(s1), lcount(s1), lcount(s2));
        if(a <= S1 - 1) myexit(0);
        a = compute(c, rcount(s2), lcount(s1), lcount(s2));
        if(a <= S1) cand.push_back(s1.size() * S1 + ssize(s2) - rcount(s2));
    }
    if(rcount(s1) + lcount(s2) >= c) cand.push_back(s1.size() * (S1-1) + ssize(s1) - rcount(s1));
    if(rcount(s2) + lcount(s2) >= c) cand.push_back(2*s1.size() * (S1) + s2.size() + ssize(s2) - rcount(s2));
    if(rcount(s2) + lcount(s1) >= c) cand.push_back(s1.size() * (S1) + ssize(s2) - rcount(s2));
    if(lcount(s2) == s2.size()) {
        ll a;
        a = compute(c, rcount(s1), lcount(s2), lcount(s1));
        a = max<ll>(a, 1);
        cand.push_back(ssize(s1) * S1 * (a-1) + s1.size() * (S1-1) +  ssize(s2) * (a-1)*a/2 + ssize(s1) - rcount(s1));
    }


    sort(cand.begin(), cand.end());
    if(cand.empty()) myexit(-1);
    myexit(cand[0]);
}