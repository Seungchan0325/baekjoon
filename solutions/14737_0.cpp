#include <bits/stdc++.h>

using namespace std;

#define TO_IDX(r, c) ((r-1) * W + (c))
#define STOP(r, c) (5*TO_IDX(r, c))
#define LEFT(r, c) (5*TO_IDX(r, c) + 1)
#define RIGHT(r, c) (5*TO_IDX(r, c) + 2)
#define UP(r, c) (5*TO_IDX(r, c) + 3)
#define DOWN(r, c) (5*TO_IDX(r, c) + 4)

const int MAXW = 55;
const int SZ = 10 * MAXW * MAXW;

int H, W;
bool visited[SZ], rev_visited[SZ];
char puzzle[MAXW][MAXW];
vector<int> graph[SZ], tmp[SZ], rev_graph[SZ];

bool inStack[SZ];
int pv, num[SZ], low[SZ], scc[SZ], t;
stack<int> s;

void find_scc(int u)
{
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

void rev_dfs(int u)
{
    rev_visited[u] = true;
    for(auto v : rev_graph[u]) {
        if(!rev_visited[v]) rev_dfs(v);
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
    vector<array<int, 2>> stars;
    vector<pair<int, int>> edges;

    for(int i = 1; i <= H; i++) {
        for(int j = 1; j <= W; j++) {
            // cout << TO_IDX(i, j) << " ";
            if(puzzle[i][j] == '#') continue;
            else if(puzzle[i][j] == 'O') ball = STOP(i, j);
            else if(puzzle[i][j] == '*') {
                stars.push_back({LEFT(i, j), UP(i, j)});
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

            if(puzzle[i+1][j] == '.' || puzzle[i+1][j] == '*' || puzzle[i+1][j] == 'O') edges.emplace_back(DOWN(i, j), DOWN(i+1, j));
            else edges.emplace_back(DOWN(i, j), STOP(i, j));
        }
        // cout << "\n";
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

    for(auto [u, v] : edges) {
        u = scc[u];
        v = scc[v];

        if(u == v || u == 0 || v == 0) continue;

        // cout << u << " " << v << "\n";

        graph[u].push_back(v);
        rev_graph[v].push_back(u);
    }

    // cout << "----------------\n";

    tmp[2*scc[ball]+1].push_back(2*scc[ball]);

    for(int i = 0; i < stars.size(); i++) {
        int a = scc[stars[i][0]];
        int b = scc[stars[i][1]];
        if(!a && !b) goto NO;
        if(!a || !b) {
            if(a == 0) a = b;
            tmp[2*a+1].push_back(2*a);
            // cout << 2*a+1 << " " << 2*a << "\n";
        } else {
            tmp[2*a+1].push_back(2*b);
            // cout << 2*a+1 << " " << 2*b << "\n";
            tmp[2*b+1].push_back(2*a);
            // cout << 2*b+1 << " " << 2*a << "\n";
        }
    }
    // cout << "----------------\n";

    for(int i = 1; i <= t; i++) {
        memset(visited, 0, sizeof(visited));
        dfs(i);
        memset(rev_visited, 0, sizeof(rev_visited));
        rev_dfs(i);
        for(int j = 1; j <= t; j++) {
            if(visited[j] == false && rev_visited[j] == false) {
                tmp[2*i].push_back(2*j+1);
                tmp[2*j].push_back(2*i+1);
                // cout << 2*i << " " << 2*j+1 << "\n";
                // cout << 2*j << " " << 2*i+1 << "\n";
            }
        }
    }

    for(int i = 1; i <= t; i++) {
        graph[i].clear();
    }

    for(int i = 2; i <= 2*t+1; i++) {
        graph[i] = tmp[i];
    }

    {
    int old_t = t;

    memset(inStack, 0, sizeof(inStack));
    pv = t = 0;
    memset(num, 0, sizeof(num));
    memset(low, 0, sizeof(low));
    memset(scc, 0, sizeof(scc));
    s = stack<int>();

    for(int i = 2; i <= 2*old_t+1; i++) {
        if(!num[i]) find_scc(i);
    }

    for(int i = 1; i <= old_t; i++) {
        if(scc[2*i] == scc[2*i+1]) {
            goto NO;
        }
    }
    }

    cout << "YES";
    return 0;
NO:
    cout << "NO";
}