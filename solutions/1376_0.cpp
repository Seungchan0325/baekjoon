#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, m;
bool visited[MAXN];
vector<int> graph[MAXN];
vector<int> trees[MAXN];

void update(int tree, int start, int end, int index, int pos, int value)
{
    if(end < pos || pos < start) return;

    if(start == end) {
        trees[tree][index] = value;
        return;
    }

    int mid = (start + end) / 2;
    update(tree, start, mid, 2*index, pos, value);
    update(tree, mid+1, end, 2*index+1, pos, value);
    trees[tree][index] = trees[tree][2*index] + trees[tree][2*index+1];
}

int kth(int tree, int start, int end, int index, int k)
{
    if(start == end) return start;
    
    int mid = (start + end) / 2;

    if(k <= trees[tree][2*index]) {
        return kth(tree, start, mid, 2*index, k);
    } else {
        return kth(tree, mid+1, end, 2*index+1, k - trees[tree][2*index]);
    }
}

void mFS(int node)
{
    cout << node << " ";
    visited[node] = true;
    trees[node].resize(4*graph[node].size());
    for(int i = 0; i < graph[node].size(); i++) {
        if(visited[graph[node][i]]) {
            int pos = lower_bound(graph[graph[node][i]].begin(), graph[graph[node][i]].end(), node) - graph[graph[node][i]].begin();
            update(graph[node][i], 0, graph[graph[node][i]].size() - 1, 1, pos, 0);
        } else {
            update(node, 0, graph[node].size() - 1, 1, i, 1);
        }
    }

    while(0 < trees[node][1]) {
        int k = (trees[node][1] & 1) ? trees[node][1] / 2 + 1 : 1;
        int next = graph[node][kth(node, 0, graph[node].size() - 1, 1, k)];
        mFS(next);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if(u == v) continue;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for(int i = 1; i <= n; i++) {
        sort(graph[i].begin(), graph[i].end());
        graph[i].erase(unique(graph[i].begin(), graph[i].end()), graph[i].end());
    }


    mFS(1);
}