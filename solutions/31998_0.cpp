#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int B = 400;

struct Bucket
{
    ll sum = 0, cnt = 0;
    vector<ll> arr;
    void insert(int x, ll h)
    {
        sum += h;
        cnt++;
        arr.insert(arr.begin() + x, h);
    }

    void erase(int x)
    {
        sum -= arr[x];
        cnt--;
        arr.erase(arr.begin() + x);
    }

    int query(ll t, ll b)
    {
        int ret = 0;
        ll s = 0;
        for(ll h : arr) {
            s += h;
            if(s > t && (s - h) < b) ret++;
        }
        return ret;
    }
};

int N, Q;
vector<Bucket> buckets;

void build(vector<ll> h)
{
    int n = h.size();
    // int sqrtn = sqrt(n);
    buckets.clear();
    buckets.resize((n + B - 1) / B);
    for(int i = 0; i < n; i++) {
        buckets[i/B].sum += h[i];
        buckets[i/B].cnt++;
        buckets[i/B].arr.push_back(h[i]);
    }
}

void insert(int x, ll h)
{
    int idx = 0;
    while(idx + 1 < buckets.size() && (x - buckets[idx].cnt) > 0) {
        x -= buckets[idx].cnt;
        idx++;
    }
    buckets[idx].insert(x, h);
}

void erase(int x)
{
    int idx = 0;
    while(idx + 1 < buckets.size() && (x - buckets[idx].cnt) >= 0) {
        x -= buckets[idx].cnt;
        idx++;
    }
    buckets[idx].erase(x);
}

int query(ll t, ll b)
{
    int ret = 0;
    int idx = 0;
    ll s = 0;
    while(idx + 1 < buckets.size() && (s + buckets[idx].sum) <= t) {
        s += buckets[idx].sum;
        idx++;
    }
    ret += buckets[idx].query(t - s, b - s);
    s += buckets[idx++].sum;
    while(idx + 1 < buckets.size() && (s + buckets[idx].sum) <= b) {
        ret += buckets[idx].cnt;
        s += buckets[idx].sum;
        idx++;
    }
    if(idx < buckets.size()) ret += buckets[idx].query(t - s, b - s);
    return ret;
}

void print()
{
    // cout << "\n";
    for(int i = 0; i < buckets.size(); i++) {
        for(auto j : buckets[i].arr) cout << j << " ";
        // cout << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> Q;
    vector<ll> h(N);
    for(auto& i : h) cin >> i;
    build(h);
    // print();
    while(Q--) {
        if(Q % B == 0) {
            vector<ll> h;
            for(auto& buck : buckets) h.insert(h.end(), buck.arr.begin(), buck.arr.end());
            build(h);
        }

        int op;
        cin >> op;

        if(op == 1) {
            int i, h;
            cin >> i >> h;
            insert(i-1, h);
        } else if(op == 2) {
            int i;
            cin >> i;
            erase(i-1);
        } else {
            ll t, b;
            cin >> t >> b;
            int ans = query(t, b);
            cout << ans << "\n";
        }
        // print();
    }
}