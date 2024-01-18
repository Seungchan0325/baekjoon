#include <bits/stdc++.h>

using namespace std;

struct Coord {
    int r;
    int c;

    bool operator==(const Coord& other) {
        return r == other.r && c == other.c;
    }
};

struct Node {
    int cost;
    vector<Coord> path;

    bool operator<(Node other) const {
        return cost > other.cost;
    }
};

const int MAXN = 51;
const pair<int, int> dir[] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

bool visited[MAXN][MAXN], circuit[MAXN][MAXN];

void line_to(Coord s, Coord e) {
    for(int r=min(s.r, e.r); r<=max(s.r, e.r); r++) circuit[r][s.c] = true;
    for(int c=min(s.c, e.c); c<=max(s.c, e.c); c++) circuit[s.r][c] = true;
}

bool in_range(int x, int n) {
    return 1 <= x && x <= n;
}

int get_cost(int r, int c, int k) {
    return circuit[r][c] ? k : 1;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, m, k;
    Coord s, e;
    cin>>n;
    cin>>s.r>>s.c>>e.r>>e.c;
    cin>>k;
    cin>>m;
    while(m--) {
        int l; cin>>l;
        vector<Coord> coords(l);
        for(auto& [r, c] : coords) cin>>r>>c;
        for(int i=0; i<l-1; i++)
            line_to(coords[i], coords[i+1]);
    }

    priority_queue<Node> pq;
    visited[s.r][s.c] = true;
    pq.push({get_cost(s.r, s.c, k), {s}});

    Node ans;
    while(!pq.empty()) {
        auto [cost, path] = pq.top();
        if(path.back() == e) ans = pq.top();
        pq.pop();

        for(int i=0; i<4; i++) {
            int nr = path.back().r + dir[i].first;
            int nc = path.back().c + dir[i].second;

            if(!in_range(nr, n) || !in_range(nc, n)) continue;
            if(visited[nr][nc]) continue;

            int ncost = cost + get_cost(nr, nc, k);
            visited[nr][nc] = true;
            path.push_back({nr, nc});
            pq.push({ncost, path});
            path.pop_back();
        }
    }

    vector<Coord> path;
    path.push_back(ans.path[0]);
    for(int i=1; i<ans.path.size()-1; i++) {
        if((ans.path[i-1].r == ans.path[i].r && ans.path[i+1].c == ans.path[i].c)
            || (ans.path[i-1].c == ans.path[i].c && ans.path[i+1].r == ans.path[i].r))
            path.push_back(ans.path[i]);
    }
    path.push_back(ans.path.back());

    cout<<ans.cost<<"\n";
    cout<<path.size()<<" ";
    for(auto [r, c] : path) {
        cout<<r<<" "<<c<<" ";
    }
}