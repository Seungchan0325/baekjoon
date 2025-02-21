#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 303030;


int N, p[MAXN];
ll x[MAXN];
vector<int> g[MAXN];

bool merge_a(pair<ll, ll>& a, pair<ll, ll> b)
{
    if(a.second >= b.first) {
        a.second = a.second - b.first + b.second;
        return true;
    }
    if(a.first >= a.second) {
        a.first = a.first - a.second + b.first;
        a.second = b.second;
        return true;
    }
    return false;
}

bool merge_b(pair<ll, ll> a, pair<ll, ll>& b)
{
    if(a.second >= b.first) {
        b.second = a.second - b.first + b.second;
        b.first = a.first;
        return true;
    }
    if(a.first >= a.second) {
        b.first = a.first - a.second + b.first;
        return true;
    }
    return false;
}

void merge(set<pair<ll, ll>>& small, set<pair<ll, ll>>& large)
{
    vector<pair<ll, ll>> erased;
    for(auto i : small) {
        auto j = large.lower_bound(i);
        while(true) {
            if(j == large.end()) break;
            if(!merge_a(i, *j)) break;
            erased.push_back(*j);
            ++j;
        }
        for(auto item : erased) large.erase(item);
        erased.clear();

        j = large.lower_bound(i);
        while(true) {
            if(j == large.begin()) break;
            --j;
            if(!merge_b(*j, i)) break;
            erased.push_back(*j);
        }
        for(auto item : erased) large.erase(item);
        erased.clear();

        large.insert(i);
    }
}

set<pair<ll, ll>> dfs(int u)
{
    set<pair<ll, ll>> s;
    
    for(auto v : g[u]) {
        auto ss = dfs(v);
        
        if(s.size() < ss.size()) swap(s, ss);
        merge(ss, s);
    }

    set<pair<ll, ll>> ss;
    
    pair<ll, ll> first;
    if(x[u] > 0) first = {0, x[u]};
    else first = {-x[u], 0};

    while(s.size() && merge_a(first, *s.begin())) s.erase(s.begin());
    s.insert(first);

    if(s.size() == 1 && s.begin()->first >= s.begin()->second) s.clear();

    return s;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> x[0];
    for(int i = 1; i <= N; i++) {
        cin >> x[i] >> p[i];
        g[p[i]].push_back(i);
    }
    
    auto s = dfs(0);
    ll mx = 0, sum = 0;
    // for(auto it : s) {
    //     cout << it.first << " " << it.second << "\n";
    // }
    for(auto it : s) {
        sum += -it.first;
        if(sum < 0) break;
        sum += it.second;
        mx = max(mx, sum);
    }
    cout << mx - x[0] << "\n";
}