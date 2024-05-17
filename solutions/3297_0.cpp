#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;

int N, cache[105][105], sec;

int ccw(int x0, int y0, int x1, int y1, int x2, int y2)
{
    return (x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0);
}

int f(vector<pair<int, int>>& v, int pp, int p)
{
    int& ret = cache[pp][p];
    if(ret != -1) return ret;

    ret = -INF;
    if(ccw(v[pp].first, v[pp].second, v[p].first, v[p].second, v[0].first, v[0].second) < 0 &&
       ccw(v[p].first, v[p].second, v[0].first, v[0].second, v[sec].first, v[sec].second) < 0) {
        ret = 0;
    }

    for(int i = p + 1; i <= N; i++) {
        if(ccw(v[pp].first, v[pp].second, v[p].first, v[p].second, v[i].first, v[i].second) < 0) {
            ret = max(ret, f(v, p, i) + 1);
        }
    }

    return ret;
}

int main()
{
    cin >> N;
    vector<pair<int, int>> v;
    v.emplace_back(0, 0);
    for(int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        v.emplace_back(x, y);
    }
    sort(v.begin() + 1, v.end(), [](pair<int, int> a, pair<int, int> b) {
        int c = ccw(0, 0, a.first, a.second, b.first, b.second);
        if(c == 0) return a.first * a.first < b.first * b.first;
        return c < 0;
    });

    int result = -INF;
    for(int i = 1; i <= N; i++) {
        memset(cache, -1, sizeof(cache));
        sec = i;
        result = max(result, f(v, 0, i) + 2);
    }
    cout << result;
}