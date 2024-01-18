#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000005;

int n, tree[4*MAXN];
vector<pair<int, int>> v;

void update(int pos, int delta, int start = 0, int end = n - 1, int index = 1)
{
    if(end < pos || pos < start) return;

    if(start == end) {
        tree[index] += delta;
        return;
    }

    int mid = (start + end) / 2;
    update(pos, delta, start, mid, 2*index);
    update(pos, delta, mid+1, end, 2*index+1);
    tree[index] = max(tree[2*index], tree[2*index+1]);
}

int query(int left, int right, int start = 0, int end = n - 1, int index = 1)
{
    if(end < left || right < start) return 0;

    if(left <= start && end <= right) return tree[index];

    int mid = (start + end) / 2;
    return max(query(left, right, start, mid, 2*index), query(left, right, mid+1, end, 2*index+1));
}

int main()
{
    cin >> n;
    v.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].second = i;
    }

    sort(v.begin(), v.end(), [](pair<int, int> a, pair<int, int> b) {
        if(a.first != b.first) return a.first < b.first;
        return b.second < a.second;
    });
    for(auto [value, idx] : v) {
        int max_v = query(0, idx);
        update(idx, max_v + 1);
    }
    cout << tree[1];
}