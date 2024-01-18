#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Q {
    int idx, i, j, k;
};

const int MAXN = 50005;
const int M = 4*MAXN;

int n, indexes[2*MAXN];
ll lazy[4*M];
pair<ll, int> tree[4*M];
vector<Q> q1, q2;
vector<pair<int, ll>> ans;

void update_size(int start, int end, int index, int pos, int v) {
    if(end < pos || pos < start) return;

    if(start == end) {
        tree[index].second = v;
        return;
    }

    int mid = (start + end) / 2;
    update_size(start, mid, 2*index, pos, v);
    update_size(mid+1, end, 2*index+1, pos, v);
    tree[index].second = tree[2*index].second + tree[2*index+1].second;
}

void propagate(int start, int end, int index) {
    if(lazy[index]) {
        tree[index].first += tree[index].second * lazy[index];
        if(start != end) {
            lazy[2*index] += lazy[index];
            lazy[2*index+1] += lazy[index];
        }
        lazy[index] = 0;
    }
}

void update(int start, int end, int index, int left, int right, ll delta) {
    propagate(start, end, index);
    if(end < left || right < start) return;
    if(left <= start && end <= right) {
        tree[index].first += tree[index].second * delta;
        if(start != end) {
            lazy[2*index] += delta;
            lazy[2*index+1] += delta;
        }
        return;
    }

    int mid = (start + end) / 2;
    update(start, mid, 2*index, left, right, delta);
    update(mid+1, end, 2*index+1, left, right, delta);
    tree[index].first = tree[2*index].first + tree[2*index+1].first;
}

ll query(int start, int end, int index, int left, int right) {
    propagate(start, end, index);
    if(end < left || right < start) return 0;
    if(left <= start && end <= right) return tree[index].first;
    
    int mid = (start + end) / 2;
    return query(start, mid, 2*index, left, right) + 
           query(mid+1, end, 2*index+1, left, right);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;

    vector<int> vs;
    vs.reserve(2*n);
    for(int q = 0; q < n; q++) {
        int t, i, j, k;
        cin >> t >> i >> j >> k;
        if(t == 1) q1.push_back({q, i, j, k});
        else q2.push_back({q, i, j, k-1});
        vs.push_back(i);
        vs.push_back(j);
    }
    sort(q2.begin(), q2.end(), [](Q a, Q b) { return a.k < b.k; });

    sort(vs.begin(), vs.end());
    vs.erase(unique(vs.begin(), vs.end()), vs.end());

    int size = 0;
    indexes[0] = size;
    update_size(0, M, 1, size++, 1);
    for(int i = 1; i < vs.size(); i++) {
        if(vs[i-1] + 1 != vs[i])
            update_size(0, M, 1, size++, vs[i] - vs[i-1] - 1);

        indexes[i] = size;
        update_size(0, M, 1, size++, 1);
    }

    int prev_k = -1;
    for(auto [idx, i, j, k] : q2) {
        while(prev_k < k) {
            auto [i_, s, e, delta] = q1[++prev_k];
            int left = indexes[lower_bound(vs.begin(), vs.end(), s)-vs.begin()];
            int right = indexes[lower_bound(vs.begin(), vs.end(), e)-vs.begin()];
            update(0, M, 1, left, right, delta);
        }
        int left = indexes[lower_bound(vs.begin(), vs.end(), i)-vs.begin()];
        int right = indexes[lower_bound(vs.begin(), vs.end(), j)-vs.begin()];
        ans.emplace_back(idx, query(0, M, 1, left, right));
    }
    sort(ans.begin(), ans.end());
    
    for(auto [idx, ans_] : ans) {
        cout << ans_ << "\n";
    }
}