#include <bits/stdc++.h>

using namespace std;

using ll = long long;

string find(ll n, ll d)
{
    bool chk[30303] = {};
    ll a = d % n;
    int i = 0;
    while(true) {
        i++;
        a = ((a * 10) % n + d) % n;
        if(a == 0) {
            string ret = to_string(d);
            ret.append(i, to_string(d)[0]);
            return ret;
        }
        if(chk[a]) break;
        chk[a] = true;
    }
    return "";
}

bool vst[30303];
int par[30303];
string find(ll n, ll a, ll b)
{
    ll aa = a;
    memset(vst, 0, sizeof(vst));
    memset(par, 0, sizeof(par));
    queue<ll> q;
    q.push(a%n);
    vst[a%n] = true;
    if(a > b) swap(a, b);
    while(!q.empty()) {
        ll w = q.front(); q.pop();
        ll wa = (10*w+a)%n;
        ll wb = (10*w+b)%n;
        if(!vst[wa]) q.push(wa), vst[wa] = true, par[wa] = w;
        if(!vst[wb]) q.push(wb), vst[wb] = true, par[wb] = w;
    }

    if(!vst[0]) return "";
    ll w = 0;
    string s;
    while(w != aa%n) {
        if((10*par[w]+a)%n == w) s.push_back('0'+a);
        else s.push_back('0'+b);
        w = par[w];
    }
    s += to_string(aa);
    reverse(s.begin(), s.end());
    return s;
}

int main()
{
    ll n;
    cin >> n;

    vector<string> ans;
    for(ll d = 1; d < 10; d++) {
        auto s = find(n, d);
        if(s != "") ans.push_back(s);
    }
    if(ans.size()) {
        sort(ans.begin(), ans.end(), [](string&a, string&b){
            if(a.size() != b.size()) return a.size() < b.size();
            return a < b;
        });
        cout << ans[0];
        return 0;
    }

    for(int i = 1; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            auto s = find(n, i, j);
            if(s != "") ans.push_back(s);
        }
    }
    if(ans.size()) {
        sort(ans.begin(), ans.end(), [](string&a, string&b){
            if(a.size() != b.size()) return a.size() < b.size();
            return a < b;
        });
        cout << ans[0];
        return 0;
    }
}