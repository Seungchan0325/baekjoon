#include <bits/stdc++.h>

using namespace std;

const int INF = 98764321;

struct Medals {
    int gold;
    int silver;
    int bronze;
    int team;

    bool operator < (const Medals& rhs) const
    {
        if(gold != rhs.gold) return gold < rhs.gold;
        if(silver != rhs.silver) return silver < rhs.silver;
        if(bronze != rhs.bronze) return bronze < rhs.bronze;
        return team > team;
    }

    bool operator > (const Medals& rhs) const
    {
        if(gold != rhs.gold) return gold > rhs.gold;
        if(silver != rhs.silver) return silver > rhs.silver;
        if(bronze != rhs.bronze) return bronze > rhs.bronze;
        return team < team;
    }
};

int n, l, cache[55][55];
vector<Medals> v;

int dp(int idx, int remain_silver)
{
    if (idx == 0) {
        return 0;
    }
    int& ret = cache[idx][remain_silver];
    if (ret != -1) {
        return ret;
    }

    int silver_usage = v[0].silver - v[idx].silver;
    int bronze_usage = v[0].bronze - v[idx].bronze + 1;

    ret = INF;
    if(v[0] < v[idx]) {
        ret = dp(idx - 1, remain_silver);
    } else {
        if(silver_usage + bronze_usage <= l) {
            ret = dp(idx - 1, remain_silver) + max(v[0].bronze - v[idx].bronze + 1, 0);
        }
        if(v[0].silver - v[idx].silver < l && remain_silver > 0) {
            ret = min(dp(idx - 1, remain_silver - 1), ret);
        }
    }

    return ret;
}

int main()
{
    cin >> n >> l;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        auto& [g, s, b, t] = v[i];
        t = i;
        cin >> g >> s >> b;
    }
    sort(v.begin() + 1, v.end(), greater<>());
    v[0].gold += l;

    int last = 1;
    int silver_usage = 0;
    while(last < n && v[0] < v[last]) last++;

    for (; last < n; last++) {
        if(v[0].gold != v[last].gold) {
            break;
        }

        silver_usage += max(0, v[0].silver - v[last].silver);
        if(l < silver_usage) {
            break;
        }

        memset(cache, -1, sizeof(cache));
        int bronze_usage = dp(last, min(l - silver_usage, 50));
        if(l < bronze_usage) {
            break;
        }
    }
    cout << last;
}