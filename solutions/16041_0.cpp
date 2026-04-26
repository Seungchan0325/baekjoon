#include <bits/stdc++.h>

using namespace std;

const int MAXN = 202020;

const int mod = 1e9 + 7;

bool chk[MAXN];
int n, m, deg[MAXN], A, B[MAXN];
vector<int> g[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }

    priority_queue<pair<int, int>> pq;
    for(int i = 1; i <= n; i++) {
        pq.push({-deg[i], i});
    }

    // 관찰
    //
    // 아무 더블 클리크를 찾자. 그러면 클리크 - 독립집합으로 나타낼 수 있다.
    // 이들의 정점 집합을 C, I라고 하자.
    // 아래 2가지를 관찰할 수 있다.
    // C != C`, I != I`인 더블 클리크를 가정하자.
    // |C` and I| <= 1을 만족한다.
    // |I` and C| <= 1을 만족한다.
    //
    // -> 아무 더블 클리크를 찾자.
    // 그 다음 클리크에서 하나씩 빼면서 I에서 넣을 수 있는 개수를 계산한다.
    //
    // 더블 클리크를 어떻게 찾나?
    // 클리크라면 차수가 크기-1이다.
    // pq로 차수를 관리하면서 남은 정점보다 적으면 지우자
    //
    // 독립집합인 것에 집중하자
    //
    // 이 과정이 끝나면 남은 정점의 차수는 크기 - 1이다.
    // 따라서 남은 정점은 클리크
    //
    // 지운 정점이 독립집합인지 확인하자. 만약 그렇지 않다면 답은 0이다.
    //
    // 지운 정점 중 차수가 |C|인 정점의 수를 세자. 그리고 이것은 A라고 하자. -> 클리크에 포함할 수 있다.
    // 지운 정점 중 차수가 |C|-1인 정점에서 {1, ..., N} - adj(u) = {i} = B[u]
    // -> i를 클리크에서 제거하면 클리크에 포함할 수 있다.
    //
    // 독립집합과 간선이 없는 정점은 전부 독립집합으로 뺄 수 있다.

    int clique = n;
    while(pq.size() && -pq.top().first < clique-1) {
        auto u = pq.top().second; pq.pop();
        if(chk[u]) continue;
        chk[u] = true;
        clique--;
        for(auto v : g[u]) {
            --deg[v];
            // pq.push({-deg[v], v});
        }
    }

    // 2번 과정
    bool ok = true;
    for(int i = 1; i <= n; i++) {
        if(!chk[i]) {
            // 클리크여야한다.
            if(deg[i] != clique-1) ok = false;
        } else {
            // 독립집합이어야한다.
            for(auto j : g[i]) {
                if(chk[j]) ok = false;
            }
        }
    }

    if(!ok) {
        cout << "0\n";
        return 0;
    }

    vector<int> inclique;
    for(int i = 1; i <= n; i++) if(!chk[i]) inclique.push_back(i);
    for(int i = 1; i <= n; i++) {
        if(!chk[i]) continue;
        if(g[i].size() == clique) A++;
        else if(g[i].size()+1 == clique) {
            int k = -1;
            sort(g[i].begin(), g[i].end());
            for(auto j : inclique) {
                if(!binary_search(g[i].begin(), g[i].end(), j)) {
                    k = j;
                    break;
                }
            }
            B[k]++;
        }
    }

    // 답구하기
    int ans = 1 + A;
    for(int i = 1; i <= n; i++) {
        if(chk[i]) continue;
        bool hasout = false;
        for(auto j : g[i]) if(chk[j]) hasout = true;
        if(!hasout) ans = (ans + 1 + A + B[i]) % mod;
    }
    cout << ans << "\n";
}
