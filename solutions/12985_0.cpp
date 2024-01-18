#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<ll, ll>;

const ll MAXN = 50005;

ll n, sum_tree[4*MAXN], cnt_tree[4*MAXN];
pii users[MAXN];

void update(ll tree[], ll start, ll end, ll index, ll pos, ll delta) {
    if(end < pos || pos < start) return;

    if(start == end) {
        tree[index] += delta;
        return;
    }

    ll mid = (start + end) / 2;
    update(tree, start, mid, 2*index, pos, delta);
    update(tree, mid+1, end, 2*index+1, pos, delta);
    tree[index] = tree[2*index] + tree[2*index+1];
}

ll query(ll tree[], ll start, ll end, ll index, ll left, ll right) {
    if(end < left || right < start) return 0;
    if(left <= start && end <= right) return tree[index];

    ll mid = (start + end) / 2;
    return query(tree, start, mid, 2*index, left, right) +
           query(tree, mid+1, end, 2*index+1, left, right);
}

int main() {
    cin >> n;
    for(ll i = 0; i < n; i++) cin >> users[i].first >> users[i].second;

    ll sum = 0;
    sort(users, users+n);
    for(ll i = 0; i < n; i++) {
        ll left_sum = query(sum_tree, 0, MAXN, 1, 0, users[i].second);
        ll right_sum = query(sum_tree, 0, MAXN, 1, users[i].second, MAXN);
        ll left_cnt = query(cnt_tree, 0, MAXN, 1, 0, users[i].second);
        ll right_cnt = query(cnt_tree, 0, MAXN, 1, users[i].second, MAXN);
        sum += users[i].first*(right_sum - right_cnt*users[i].second + left_cnt*users[i].second - left_sum);

        update(sum_tree, 0, MAXN, 1, users[i].second, users[i].second);
        update(cnt_tree, 0, MAXN, 1, users[i].second, 1);
    }
    cout << sum;
}