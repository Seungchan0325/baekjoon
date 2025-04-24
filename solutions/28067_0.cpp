#include <bits/stdc++.h>

using namespace std;

struct Point {
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    int x, y;
};

int dist(Point a, Point b)
{
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int ccw(Point a, Point b, Point c)
{
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<Point> p;
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= m; j++) {
            p.emplace_back(i, j);
        }
    }

    vector<tuple<int, int, int>> v;
    for(int i = 0; i < p.size(); i++) for(int j = i+1; j < p.size(); j++) for(int k = j+1; k < p.size(); k++) {
        if(ccw(p[i], p[j], p[k]) == 0) continue;
        int a = dist(p[i], p[j]);
        int b = dist(p[j], p[k]);
        int c = dist(p[k], p[i]);
        if(a < b) swap(a, b);
        if(b < c) swap(b, c);
        if(a < b) swap(a, b);
        v.emplace_back(a, b, c);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    cout << v.size() << "\n";
}