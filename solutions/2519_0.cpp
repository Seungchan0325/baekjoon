#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;
const int MAXN3 = 3 * MAXN;
const int MAXN6 = 6 * MAXN;

bool chk[MAXN3];
int N, X1[MAXN3], X2[MAXN3], Y1[MAXN3], Y2[MAXN3];
vector<int> graph[MAXN6];

long long ccw(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3)
{
    return (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1); 
}

bool is_cross(int i, int j)
{
    return ccw(X1[i], Y1[i], X2[i], Y2[i], X1[j], Y1[j]) * ccw(X1[i], Y1[i], X2[i], Y2[i], X2[j], Y2[j]) <= 0 && ccw(X1[j], Y1[j], X2[j], Y2[j], X1[i], Y1[i]) * ccw(X1[j], Y1[j], X2[j], Y2[j], X2[i], Y2[i]) <= 0;
}

int NNOT(int a)
{
    return a<<1;
}

int NOT(int a)
{
    return a<<1|1;
}

void add(int a, int b)
{
    graph[a^1].push_back(b);
    graph[b^1].push_back(a);
}

bool inStack[MAXN6];
int pv, low[MAXN6], num[MAXN6], scc[MAXN6], t;
stack<int> s;

void dfs(int u)
{
    num[u] = low[u] = ++pv;
    inStack[u] = true;
    s.push(u);

    for(auto v : graph[u]) {
        if(!num[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if(inStack[v]) {
            low[u] = min(low[u], low[v]);
        }
    }

    if(num[u] == low[u]) {
        t++;
        while(s.top() != u) {
            scc[s.top()] = t;
            // cout << s.top() << " ";
            inStack[s.top()] = false;
            s.pop();
        }
        // cout << u << "\n";
        scc[u] = t;
        inStack[u] = false;
        s.pop();
    }
}

int main()
{
    cin >> N;
    for(int i = 1; i <= 3*N; i++) {
        cin >> X1[i] >> Y1[i] >> X2[i] >> Y2[i];
    }

    for(int i = 1; i <= N; i++) {
        int a = NOT(3 * i - 2);
        int b = NOT(3 * i - 1);
        int c = NOT(3 * i);
        add(a, b);
        add(a, c);
        add(b, c);
        add(b, a);
        add(c, a);
        add(c, b);
    }

    for(int i = 1; i <= 3*N; i++) {
        for(int j = i+1; j <= 3*N; j++) {
            if(is_cross(i, j)) {
                add(NNOT(i), NNOT(j));
            }
        }
    }

    for(int i = 2; i <= 6*N+1; i++) {
        if(!num[i]) dfs(i);
    }

    for(int i = 1; i <= 3*N; i++) {
        if(scc[NNOT(i)] == scc[NOT(i)]) {
            cout << "-1";
            return 0;
        }
    }

    vector<pair<int, int>> v;
    for(int i = 2; i <= 6*N+1; i++) {
        v.emplace_back(scc[i], i);
    }
    sort(v.begin(), v.end());

    vector<int> ans;
    for(auto [_scc, i] : v) {
        if(!chk[i/2]) {
            if(~i&1) ans.push_back(i/2);
            chk[i/2] = true;
        }
    }

    cout << ans.size() << "\n";
    for(auto i : ans) cout << i << " ";

    return 0;
}