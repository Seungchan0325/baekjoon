#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 1010101;

int N;

signed main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    vector<int> v(N);
    for(auto& i : v) cin >> i;
    sort(v.begin(), v.end());
    int ans = 0;
    for(int i = 30; i >= 0; i--) {
        vector<int> a, b;
        for(auto j : v) {
            if(j&(2LL<<i)) a.push_back(j&~(2LL<<i));
            else b.push_back(j);
        }
        merge(a.begin(), a.end(), b.begin(), b.end(), v.begin());

        int cnt = 0;
        int ps, pe, qs, qe;
        ps = pe = qs = qe = 0;
        for(int j = ssize(v)-1; j >= 0; j--) {
            while(ps < N && v[j]+v[ps] < (1LL<<i)) ps++;
            while(pe < N && v[j]+v[pe] < (2LL<<i)) pe++;
            while(qs < N && v[j]+v[qs] < (2LL<<i)+(1LL<<i)) qs++;
            while(qe < N && v[j]+v[qe] < (2LL<<i)+(2LL<<i)) qe++;
            cnt += qe - qs + pe - ps;
            if((v[j]+v[j])&(1LL<<i)) cnt++;
        }
        ans <<= 1;
        if(cnt&2) ans |= 1;
    }
    cout << ans << "\n";
}