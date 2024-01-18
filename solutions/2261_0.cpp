#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

const int INF = 987654321;

struct cmp {
    constexpr bool operator()(const pii& a, const pii& b) const {
        if(a.second == b.second) return a.first < b.first;
        return a.second < b.second;
    }
};

int dist(const pii& a, const pii& b) {
    int x = a.first - b.first;
    int y = a.second - b.second;
    return x * x + y * y;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin>>n;
    vector<pii> dots(n);
    for(auto& [x, y] : dots) cin>>x>>y;

    sort(dots.begin(), dots.end());

    int closest_distance = dist(dots[0], dots[1]);
    set<pii, cmp> s{dots[0], dots[1]};
    int last = 0;

    for(int i=2; i<n; i++) {
        int rt_dist = sqrt(closest_distance);
        int lx = dots[i].first - rt_dist - 1;
        int ly = dots[i].second - rt_dist - 1;
        int ry = dots[i].second + rt_dist + 1;
        while(dots[last].first < lx && last < i)
            s.erase(dots[last++]);

        for(auto left = s.lower_bound({-INF, ly}); left->second <= ry && left != s.end(); left++)
            closest_distance = min(dist(dots[i], *left), closest_distance);

        s.insert(dots[i]);
    }

    cout<<closest_distance;
}