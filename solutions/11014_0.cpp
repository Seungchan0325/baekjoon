#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100;

const pair<int, int> d[] = {{0, 1}, {0, -1}, {-1, 1}, {-1, -1}};
bool visited[MAXN*MAXN];
int N, M, owner[MAXN*MAXN], ans;
char Class[MAXN][MAXN];
vector<int> graph[MAXN*MAXN];

int IDX(int i, int j) { return M * i + j; }

bool dfs(int u)
{
    for(auto v : graph[u]) {
        if(visited[v]) continue;
        visited[v] = true;
        if(owner[v] == -1 || dfs(owner[v])) {
            owner[v] = u;
            return true;
        }
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int C;
    cin >> C;
    while(C--) {
        memset(Class, 'x', sizeof(Class));
        ans = 0;
        cin >> N >> M;
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= M; j++) {
                cin >> Class[i][j];
                if(Class[i][j] == '.') ans++;
                graph[IDX(i, j)].clear();
            }
        }

        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= M; j += 2) {
                for(auto [di, dj] : d) {
                    if(Class[i][j] == '.' && Class[i+di][j+dj] == '.') {
                        graph[IDX(i, j)].push_back(IDX(i+di, j+dj));
                    }
                }
            }
        }

        for(int i = 1; i <= N; i++) {
            for(int j = 2; j <= M; j += 2) {
                for(auto [di, dj] : d) {
                    if(Class[i][j] == '.' && Class[i+di][j+dj] == '.') {
                        graph[IDX(i+di, j+dj)].push_back(IDX(i, j));
                    }
                }
            }
        }

        memset(owner, -1, sizeof(owner));

        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= M; j += 2) {
                memset(visited, 0, sizeof(visited));
                ans -= dfs(IDX(i, j)) ? 1 : 0;
            }
        }
        cout << ans << "\n";
    }
}