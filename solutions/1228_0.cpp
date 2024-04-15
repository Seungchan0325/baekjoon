#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int MAXN = 205;

bool isroot[MAXN];
int N, M, days[MAXN], dp[MAXN][MAXN], sz[MAXN];
vector<int> graph[MAXN];
vector<string> child[MAXN];

void dfs(int u)
{
    fill(dp[u], dp[u] + N + 1, INF);
    sz[u] = 1;
    for(auto v : graph[u]) {
        dfs(v); sz[u] += sz[v];
        for(int i = N; i >= 0; i--) {
            for(int j = 0; j <= N; j++) {
                if(i-j < 0) break;
                dp[u][i] = min(dp[u][i], dp[u][i-j] + dp[v][j]);
            }
        }
        for(int i = 0; i <= N; i++) {
            dp[u][i] = min(dp[u][i], dp[v][i]);
        }
    }

    dp[u][sz[u]] = min(dp[u][sz[u]], days[u]);
}

int main()
{
    cin >> N >> M;
    cin.ignore();

    map<string, int> idx;
    for(int i = 1; i <= N; i++) {
        string line;
        getline(cin, line);
        istringstream iss(line);

        string buf;
        getline(iss, buf, ' ');
        idx[buf] = i;

        getline(iss, buf, ' ');
        days[i] = stoi(buf);

        while(getline(iss, buf, ' ')) {
            child[i].push_back(buf);
        }
    }

    fill(isroot + 1, isroot + N + 1, true);
    for(int i = 1; i <= N; i++) {
        for(auto c : child[i]) {
            isroot[idx[c]] = false;
            graph[i].push_back(idx[c]);
        }
    }

    fill(dp[0], dp[0] + N + 1, INF);
    for(int u = 1; u <= N; u++) {
        if(isroot[u]) {
            dfs(u);
            for(int i = N; i >= 0; i--) {
                for(int j = 0; j < N; j++) {
                    if(i-j < 0) break;
                    dp[0][i] = min(dp[0][i], dp[0][i-j] + dp[u][j]);
                }
            }

            for(int i = 0; i <= N; i++) {
                dp[0][i] = min(dp[0][i], dp[u][i]);
            }
        }
    }

    int mn = INF;
    for(int i = M; i <= N; i++) {
        mn = min(dp[0][i], mn);
    }

    if(M == 0) mn = 0;

    cout << mn << "\n";
}