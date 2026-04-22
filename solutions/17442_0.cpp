#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 101010;
const int MAXM = 202020;

struct Fenwick {
    int n;
    vector<int> t;
    void init(int _n) {
        n = _n;
        t.resize(n+1);
    }
    void upd(int x, int v) {
        while(x <= n) {
            t[x] += v;
            x += x & -x;
        }
    }
    int qry(int x) {
        int ret = 0;
        while(x) {
            ret += t[x];
            x -= x & -x;
        }
        return ret;
    }
};

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

vector<vector<int>> find_faces(vector<Point> vertices, vector<vector<int>> adj)
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

int N, M, Q, C[MAXM];
vector<Point> vertices;
vector<vector<int>> adj;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M >> Q;
    vertices.resize(N);
    for(auto& v : vertices) cin >> v.x >> v.y;
    vector<pair<int, int>> events;
    adj.resize(N);
    for(int i = 1; i <= M; i++) {
        int u, v; cin >> u >> v; u--; v--;
        if(vertices[u].x > vertices[v].x) swap(u, v);
        adj[u].push_back(v);
        adj[v].push_back(u);
        events.push_back({vertices[u].x, i});
        events.push_back({vertices[v].x, -i});
    }
    vector<pair<int, int>> qrys_cut;
    vector<tuple<int, int, int, int>> qrys_face;
    for(int i = 1; i <= Q; i++) {
        int a, b; cin >> a >> b;
        if(a > b) swap(a, b);
        qrys_cut.push_back({a, i});
        qrys_cut.push_back({b, i});
        qrys_face.push_back({a, a, i, 1});
        qrys_face.push_back({a, b, i, -1});
        qrys_face.push_back({b, b, i, 1});
    }

    sort(events.begin(), events.end());
    sort(qrys_cut.begin(), qrys_cut.end());

    int p = 0;
    int num = 0;
    for(auto e : events) {
        while(p < qrys_cut.size() && qrys_cut[p].first < e.first) {
            C[qrys_cut[p].second] += num;
            p++;
        }
        if(e.second > 0) num++;
        else num--;
    }

    auto faces = find_faces(vertices, adj);
    vector<pair<int, int>> lr;
    vector<int> ys;
    for(int i = 1; i < faces.size(); i++) {
        int l = 1e9;
        int r = -1e9;
        auto face = faces[i];
        for(int j = 0; j < face.size(); j++) {
            l = min<int>(l, vertices[face[j]].x);
            r = max<int>(r, vertices[face[j]].x);
        }
        ys.push_back(r);
        lr.push_back({l, r});
    }

    sort(lr.begin(), lr.end());
    sort(qrys_face.begin(), qrys_face.end());
    for(auto [x, y, id, w] : qrys_face) ys.push_back(y);

    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    for(auto& [l, r] : lr) r = lower_bound(ys.begin(), ys.end(), r) - ys.begin() + 1;
    for(auto& [x, y, id, w] : qrys_face) y = lower_bound(ys.begin(), ys.end(), y) - ys.begin() + 1;

    p = 0;
    Fenwick f; f.init(qrys_face.size());
    for(auto [x, y, id, w] : qrys_face) {
        while(p < lr.size() && lr[p].first < x) {
            f.upd(lr[p].second, 1);
            p++;
        }
        C[id] -= w * (f.qry(ys.size()) - f.qry(y));
    }

    for(int i = 1; i <= Q; i++) {
        cout << C[i] + 1 << "\n";
    }
}
