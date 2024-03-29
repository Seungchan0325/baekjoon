#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, tree[MAXN], sz;

void update(int i, int delta)
{
    while(i <= sz) {
        tree[i] += delta;
        i += (i & -i);
    }
}

int query(int i)
{
    int ret = 0;
    while(i > 0) {
        ret += tree[i];
        i -= (i & -i);
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n;
    vector<pair<int, int>> rb(n);
    vector<int> v;
    for(auto& [r, b] : rb) {
        cin >> r >> b;
        v.push_back(b);
    }

    sort(rb.begin(), rb.end(), greater<>());
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    sz = v.size();

    long long result = 0;
    for(auto [r, b] : rb) {
        int idx = lower_bound(v.begin(), v.end(), b) - v.begin() + 1;
        result += query(idx - 1);
        update(idx, 1);
    }
    cout << result;
}