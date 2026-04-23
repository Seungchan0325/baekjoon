#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Point {
    ll x, y;
    Point(ll x = 0, ll y = 0) : x(x), y(y) {}
    Point operator + (const Point& p) const {
        return Point(x+p.x, y+p.y);
    }
    Point operator - (const Point& p) const {
        return Point(x-p.x, y-p.y);
    }
    ll cross(const Point& p) const {
        return x * p.y - y * p.x;
    }
    ll cross(const Point& p, const Point& q) const {
        return (p - *this).cross(q - *this);
    }
    auto operator <=> (const Point& p) const {
        return tuple(x, y) <=> tuple(p.x, p.y);
    }
};

struct PolorComparator {
    Point o;
    PolorComparator(const Point& o = Point(0, 0)) : o(o){}
    bool operator () (const Point& p, const Point& q) const {
        if((p < o) != (q < o)) return p < q;
        return o.cross(p, q) > 0;
    }
};

vector<vector<int>> find_faces(vector<Point>& vertices, vector<vector<int>>& adj)
{
    int n = vertices.size();
    vector<vector<char>> used(n);
    for(int i = 0; i < n; i++) {
        used[i].resize(adj[i].size());
        auto comp = PolorComparator(vertices[i]);
        sort(adj[i].begin(), adj[i].end(), [&](int i, int j) { return comp(vertices[i], vertices[j]); });
    }
    vector<vector<int>> faces;
    for(int i = 0; i < n; i++) {
        for(int edge_id = 0; edge_id < adj[i].size(); edge_id++) {
            if(used[i][edge_id]) continue;
            vector<int> face;
            int v = i;
            int e = edge_id;
            while(!used[v][e]) {
                used[v][e] = true;
                face.push_back(v);
                int u = adj[v][e];
                auto comp = PolorComparator(vertices[u]);
                int e1 = lower_bound(adj[u].begin(), adj[u].end(), v, [&](int i, int j){
                   return comp(vertices[i], vertices[j]);
                }) - adj[u].begin() + 1;
                if(e1 == adj[u].size()) e1 = 0;
                v = u;
                e = e1;
            }
            reverse(face.begin(), face.end());
            Point p1 = vertices[face[0]];
            __int128 sum = 0;
            for(int j = 0; j < face.size(); j++) {
                Point p2 = vertices[face[j]];
                Point p3 = vertices[face[(j+1)%face.size()]];
                sum += (p2-p1).cross(p3-p2);
            }
            if(sum <= 0) {
                faces.insert(faces.begin(), face);
            } else {
                faces.push_back(face);
            }
        }
    }
    return faces;
}

double nx;

struct Line {
    double a, b;
    int id;
    Line(const Point& p, const Point& q, int _id) {
        id = _id;
        a = (double)(p.y-q.y)/(p.x-q.x);
        b = a * -q.x + q.y;
    }
    double eval(double x) const { return a * x + b; }
    auto operator <=> (const Line& l) const {
        return tuple(eval(nx), id) <=> tuple(l.eval(nx), l.id);
    }
    auto operator <=> (int y) const {
        return eval(nx) <=> y;
    }
};

struct LineComp {
    using is_transparent = void;
    bool operator() (const Line& a, const Line& b) const { return a < b; }
    bool operator() (const Line& a, int y) const { return a < y; }
    bool operator() (int y, const Line& a) const { return y < a; }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    vector<Point> vertices(n);
    for(auto& v : vertices) cin >> v.x >> v.y;
    vector<tuple<int, int, int>> edges;
    vector<map<int, ll>> W(n);
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w; u--; v--;
        if(vertices[u].x > vertices[v].x) swap(u, v);
        edges.push_back({u, v, w});
        W[u][v] = w;
        W[v][u] = w;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto faces = find_faces(vertices, adj);
    int f = faces.size();
    vector<map<int, int>> idx(n);
    for(int i = 0; i < f; i++) {
        for(int j = 0; j < faces[i].size(); j++) {
            idx[faces[i][(j+1)%faces[i].size()]][faces[i][j]] = i;
        }
    }
    vector<vector<ll>> D(f, vector<ll>(f, 1e18));
    for(int i = 0; i < f; i++) D[i][i] = 0;
    for(int i = 0; i < n; i++) {
        for(auto [j, w] : W[i]) {
            int x = idx[i][j];
            int y = idx[j][i];
            D[x][y] = min(D[x][y], w);
            D[y][x] = min(D[y][x], w);
        }
    }
    for(int j = 0; j < f; j++) {
        for(int i = 0; i < f; i++) {
            for(int k = 0; k < f; k++) {
                D[i][k] = min(D[i][k], D[i][j] + D[j][k]);
            }
        }
    }

    vector<pair<int, Line>> enter, exit;
    for(auto [u, v, w] : edges) {
        if(vertices[u].x == vertices[v].x) continue;
        enter.push_back({vertices[u].x, Line(vertices[u], vertices[v], idx[u][v])});
        exit.push_back({vertices[v].x, Line(vertices[u], vertices[v], idx[u][v])});
    }

    int Q; cin >> Q;
    vector<int> where(Q+1);
    vector<array<int, 3>> Qs;
    vector<int> xs;
    for(int i = 1; i <= Q; i++) {
        int x, y; cin >> x >> y;
        xs.push_back(x);
        Qs.push_back({x, y, i});
    }
    for(auto v : vertices) xs.push_back(v.x);
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    sort(enter.begin(), enter.end());
    sort(exit.begin(), exit.end());
    sort(Qs.begin(), Qs.end());

    int p = 0;
    int q = 0;
    int k = 0;
    set<Line, LineComp> s;
    for(auto x : xs) {
        while(q < exit.size() && exit[q].first <= x) {
            nx = exit[q].first - 0.5;
            s.erase(exit[q++].second);
        }

        while(p < enter.size() && enter[p].first <= x) {
            nx = enter[p].first + 0.5;
            s.insert(enter[p++].second);
        }

        while(k < Qs.size() && Qs[k][0] <= x) {
            auto [_, y, i] = Qs[k++];
            nx = x;
            auto it = s.lower_bound(y);
            if(it == s.end()) where[i] = 0;
            else where[i] = it->id;
        }
    }

    for(int i = 1; i <= Q; i++) {
        cout << D[where[i-1]][where[i]] << "\n";
    }
}
