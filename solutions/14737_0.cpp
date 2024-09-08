#include <bits/stdc++.h>

using namespace std;

#define TO_IDX(r, c) ((r-1) * W + (c))
#define STOP(r, c) (5*TO_IDX(r, c))
#define LEFT(r, c) (5*TO_IDX(r, c) + 1)
#define RIGHT(r, c) (5*TO_IDX(r, c) + 2)
#define UP(r, c) (5*TO_IDX(r, c) + 3)
#define DOWN(r, c) (5*TO_IDX(r, c) + 4)

const int MAXW = 55;
const int SZ = 5 * MAXW * MAXW;
const int di[] = {0, -1, 1, 0, 0};
const int dj[] = {0, 0, 0, -1, 1};

int H, W, indeg[SZ];
bool visited[MAXW], is_able[SZ];
char puzzle[MAXW][MAXW];
vector<int> graph[SZ];
bitset<MAXW*MAXW> taken[SZ], take[SZ];

bool inStack[SZ];
int pv, num[SZ], low[SZ], scc[SZ], t;
stack<int> s;

void find_scc(int u)
{
    cout << u / 5 << "\n";
    num[u] = low[u] = ++pv;
    s.push(u);
    inStack[u] = true;

    for(auto v : graph[u]) {
        if(!num[v]) {
            find_scc(v);
            low[u] = min(low[u], low[v]);
        } else if(inStack[v]) {
            low[u] = min(low[u], low[v]);
        }
    }

    if(num[u] == low[u]) {
        t++;
        while(s.top() != u) {
            scc[s.top()] = t;
            inStack[s.top()] = false;
            s.pop();
        }

        scc[u] = t;
        inStack[u] = false;
        s.pop();
    }
}

void dfs(int u)
{
    visited[u] = true;
    for(auto v : graph[u]) {
        if(!visited[v]) dfs(v);
    }
}

int main()
{
    cin >> H >> W;
    for(int i = 1; i <= H; i++) {
        for(int j = 1; j <= W; j++) {
            cin >> puzzle[i][j];
        }
    }

    int ball = -1;
    vector<vector<int>> stars;
    vector<pair<int, int>> edges;

    for(int i = 1; i <= H; i++) {
        for(int j = 1; j <= W; j++) {
            cout << TO_IDX(i, j) << " ";
            if(puzzle[i][j] == '#') continue;
            else if(puzzle[i][j] == 'O') ball = STOP(i, j);
            else if(puzzle[i][j] == '*') {
                stars.push_back({STOP(i, j), LEFT(i, j), RIGHT(i, j), UP(i, j), DOWN(i, j)});
            }

            edges.emplace_back(STOP(i, j), LEFT(i, j));
            edges.emplace_back(STOP(i, j), RIGHT(i, j));
            edges.emplace_back(STOP(i, j), UP(i, j));
            edges.emplace_back(STOP(i, j), DOWN(i, j));

            if(puzzle[i][j-1] == '.' || puzzle[i][j-1] == '*' || puzzle[i][j-1] == 'O') edges.emplace_back(LEFT(i, j), LEFT(i, j-1));
            else edges.emplace_back(LEFT(i, j), STOP(i, j));

            if(puzzle[i][j+1] == '.' || puzzle[i][j+1] == '*' || puzzle[i][j+1] == 'O') edges.emplace_back(RIGHT(i, j), RIGHT(i, j+1));
            else edges.emplace_back(RIGHT(i, j), STOP(i, j));

            if(puzzle[i-1][j] == '.' || puzzle[i-1][j] == '*' || puzzle[i-1][j] == 'O') edges.emplace_back(UP(i, j), UP(i-1, j));
            else edges.emplace_back(UP(i, j), STOP(i, j));

            if(puzzle[i+1][j] == '.' || puzzle[i+1][j] == '*' || puzzle[i][j+1] == 'O') edges.emplace_back(DOWN(i, j), DOWN(i+1, j));
            else edges.emplace_back(DOWN(i, j), STOP(i, j));
        }
        cout << "\n";
    }

    for(auto [u, v] : edges) {
        graph[u].push_back(v);
    }

    find_scc(ball);

    for(int i = 1; i <= H; i++) {
        for(int j = 1; j <= W; j++) {
            graph[STOP(i, j)].clear();
            graph[LEFT(i, j)].clear();
            graph[RIGHT(i, j)].clear();
            graph[UP(i, j)].clear();
            graph[DOWN(i, j)].clear();
        }
    }

    for(int i = 0; i < stars.size(); i++) {
        for(auto& j : stars[i]) {
            j = scc[j];
            if(j) taken[j].set(i);
        }
    }

    for(auto [u, v] : edges) {
        u = scc[u];
        v = scc[v];

        if(u == v || u == 0 || v == 0) continue;

        cout << u << " " << v << "\n";

        graph[u].push_back(v);
        indeg[v]++;
    }

    for(int i = 1; i <= t; i++) {
        memset(visited, 0, sizeof(visited));
        dfs(i);

        take[i] |= taken[i];
        for(int j = 0; j < stars.size(); j++) {
            for(auto k : stars[j]) {
                if(visited[k]) take[i].set(j);
            }
        }
    }

    queue<pair<int, bitset<MAXW*MAXW>>> q;
    q.emplace(scc[ball], taken[scc[ball]]);

    while(!q.empty()) {
        auto [u, bit] = q.front(); q.pop();
        if(bit.count() == stars.size()) goto YES;
        for(auto v : graph[u]) {
            if((take[v] | bit).count() == stars.size()) {
                is_able[v] = true;
            }
            if(--indeg[v] == 0) {
                if((take[v] | bit).count() == stars.size()) {
                    q.emplace(v, taken[v] | bit);
                }
            }
        }
    }

    cout << "NO";
    return 0;
YES:
    cout << "YES";
}