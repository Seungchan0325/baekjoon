#include <bits/stdc++.h>

using namespace std;

const int MAXN = 250005;

int n, m;
pair<int, int> tree[4*MAXN];
vector<tuple<int, int, int>> v;

void init(int start, int end, int index) {
    if(start == end) {
        tree[index] = {get<1>(v[start]), start};
        return;
    }

    int mid = (start + end) / 2;
    init(start, mid, 2*index);
    init(mid+1, end, 2*index+1);
    tree[index] = max(tree[2*index], tree[2*index+1]);
}

void update(int start, int end, int index, int pos, int v) {
    if(end < pos || pos < start) return;

    if(start == end) {
        tree[index].first = v;
        return;
    }

    int mid = (start + end) / 2;
    update(start, mid, 2*index, pos, v);
    update(mid+1, end, 2*index+1, pos, v);
    tree[index] = max(tree[2*index], tree[2*index+1]);
}

pair<int, int> query(int start, int end, int index, int left, int right) {
    if(end < left || right < start) return {-1, -1};
    if(left <= start && end <= right) return tree[index];

    int mid = (start + end) / 2;
    return max(query(start, mid, 2*index, left, right), query(mid+1, end, 2*index+1, left, right));
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    v.resize(n);
    vector<int> ss;
    for(auto& [s, e, t] : v) {
        cin >> s >> e >> t;
        ss.push_back(s);
    }

    sort(ss.begin(), ss.end());
    sort(v.begin(), v.end());
    init(0, n-1, 1);

    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        int u = upper_bound(ss.begin(), ss.end(), a) - ss.begin() - 1;

        long long result = 0;
        while(true) {
            auto [e, idx] = query(0, n-1, 1, 0, u);
            if(e <= b) break;
            result += get<2>(v[idx]);
            update(0, n-1, 1, idx, -1);
        }

        cout << result << "\n";

        while(true) {
            auto [e, idx] = query(0, n-1, 1, 0, u);
            if(e <= a) break;
            update(0, n-1, 1, idx, -1);
        }

        int vv = upper_bound(ss.begin(), ss.end(), b) - ss.begin() - 1;
        while(true) {
            auto [e, idx] = query(0, n-1, 1, 0, vv);
            if(e <= b) break;
            update(0, n-1, 1, idx, -1);
        }
    }
}