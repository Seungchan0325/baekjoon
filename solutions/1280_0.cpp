#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MOD = 1'000'000'007;
const ll TREE_SZ = 200'001;

ll n;
ll cnt_tree[4*TREE_SZ], sum_tree[4*TREE_SZ];

void update(ll pos, ll delta, ll start = 0, ll end = TREE_SZ - 1, ll index = 1)
{
    if(end < pos || pos < start) return;

    if(start == end)
    {
        cnt_tree[index] = (cnt_tree[index] + delta);
        sum_tree[index] = (sum_tree[index] + start);
        return;
    }

    ll mid = (start + end) / 2;
    update(pos, delta, start, mid, 2*index);
    update(pos, delta, mid+1, end, 2*index+1);
    cnt_tree[index] = (cnt_tree[2*index] + cnt_tree[2*index+1]);
    sum_tree[index] = (sum_tree[2*index] + sum_tree[2*index+1]);
}

pair<ll, ll> query(ll left, ll right, ll start = 0, ll end = TREE_SZ - 1, ll index = 1)
{
    if(end < left || right < start) return {0, 0};
    if(left <= start && end <= right) return {cnt_tree[index], sum_tree[index]};
    
    ll mid = (start + end) / 2;
    auto l = query(left, right, start, mid, 2*index);
    auto r = query(left, right, mid+1, end, 2*index+1);
    return {(l.first + r.first), (l.second + r.second)};
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll ans = 1;
    cin >> n;
    if(n == 1)
    {
        cout << 0;
        return 0;
    }
    for(ll i = 0; i < n; i++)
    {
        ll pos;
        cin >> pos;

        if(0 < i)
        {
            auto q1 = query(0, pos);
            auto q2 = query(pos, TREE_SZ - 1);

            // ll sum = -q1.second + q2.second;
            // ll cnt = q1.first - q2.first;

            // ll cost = (sum + ((long long)cnt * pos) % MOD + MOD) % MOD;

            ll cost = ((q1.first * pos - q1.second) + (q2.second - q2.first * pos) % MOD) % MOD;

            ans = (ans * cost) % MOD;
        }

        update(pos, 1);
    }
    cout << ans;
}