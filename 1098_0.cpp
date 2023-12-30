#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

const int MAXN = 11;

int n, p, d;
pii villages[MAXN], cache[MAXN][(1<<20)+10];
vector<vector<int>> selected[MAXN];

int makeMask(int l, int r) {
    return (1<<(r+1)) - 1 - ((1<<l) - 1);
}

int Slice(int bits, int l, int r) {
    return (makeMask(l, r) & bits)>>l;
}

int inc(int bits, int l, int r) {
    int v = ((makeMask(l, r) & bits)>>l) + 1;
    int other = ~makeMask(l, r) & bits;
    return other | (v<<l);
}

int dist(int a, int b) {
    return abs(villages[a].first - villages[b].first) + abs(villages[a].second - villages[b].second);
}

vector<vector<int>> choose(int first, int last, vector<int> v) {
    if(v.size() > p) return {};

    vector<vector<int>> ret;
    if(!v.empty())
        ret.push_back(v);

    for(int second = last + 1; second < n; second++) {
        if(dist(first, second) < d) continue;
        v.push_back(second);
        auto res = choose(first, second, v);
        v.pop_back();
        for(auto& vv : res) ret.push_back(vv);
    }

    return ret;
}

bool cmp(pii a, pii b) {
    if(a.first == b.first) return b.second < a.second;
    return a.first < b.first;
}

pii dp(int first, int count) {
    if(first == n) return {0, 0};
    assert(count < (1<<20));
    auto& ret = cache[first][count];
    if(ret.first != -1) return ret;

    ret = dp(first+1, count);

    for(auto v : selected[first]) {
        if(p < Slice(count, 2*first, 2*first+1) + v.size()) continue;

        bool flag = false;
        for(auto i : v)
            if(p <= Slice(count, 2*i, 2*i+1)) {
                flag = true;
                break;
            }
        if(flag) continue;

        int ncount = count;
        int sum = 0;
        for(auto i : v) {
            ncount = inc(ncount, 2*i, 2*i+1);
            ncount = inc(ncount, 2*first, 2*first+1);
            sum += dist(i, first);
        }

        auto res = dp(first+1, ncount);
        res.first += v.size();
        res.second += sum;

        ret = max(ret, res, cmp);
    }

    return ret;
}

int main() {
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> villages[i].first >> villages[i].second;
    cin >> p >> d;

    for(int i = 0; i < n; i++) {
        selected[i] = choose(i, i, {});
    }

    memset(cache, -1, sizeof(cache));
    auto [cnt, sum] = dp(0, 0);
    cout << cnt << " " << sum;
}