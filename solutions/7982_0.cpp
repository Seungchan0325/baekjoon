#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000005;

bool vst[MAXN];
int N, A[MAXN], root[MAXN], group[MAXN], nxt[MAXN];

int find(int x)
{
    if(root[x] == x) return x;
    return root[x] = find(root[x]);
}

void merge(int x, int y)
{
    x = find(x);
    y = find(y);
    root[y] = x;
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> A[i];
    }

    iota(root, root + N + 1, 0);

    set<pair<int, int>> s;
    for(int i = 1; i <= N; i++) {
        s.emplace(A[i], i);
    }

    for(int i = 1; i <= N; i++) {
        auto it = s.lower_bound({A[i], i});
        if(it != s.begin()) {
            while(true) {
                it--;
                merge(it->second, i);
                if(vst[it->second]) break;
                vst[it->second] = true;
                if(it == s.begin()) break;
            }
        }
        s.erase(pair{A[i], i});
    }

    int idx = 0;
    memset(vst, 0, sizeof(vst));
    vector<vector<int>> v;
    for(int i = 1; i <= N; i++) {
        int j = find(i);
        if(!vst[j]) {
            v.push_back({});
            group[j] = idx++;
            vst[j] = true;
        }
        v[group[j]].push_back(i);
    }
    for(auto& i : v) sort(i.begin(), i.end());
    stable_sort(v.begin(), v.end());
    cout << v.size() << "\n";
    for(auto& i : v) {
        cout << i.size() << " ";
        for(auto& j : i) cout << j << " ";
        cout << "\n";
    }
}