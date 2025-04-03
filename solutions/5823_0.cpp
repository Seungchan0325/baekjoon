#include <bits/stdc++.h>

using namespace std;

const int MAXN = 150505;
const int B = 400;

int N, L, M, x[MAXN];

struct Bucket
{
    vector<int> xs;
    vector<int> c, n;
    void add(int x)
    {
        auto it = lower_bound(xs.begin(), xs.end(), x);
        xs.insert(it, x);
    }
    void erase(int x)
    {
        auto it = lower_bound(xs.begin(), xs.end(), x);
        xs.erase(it);
    }
    void compute()
    {
        c.resize(xs.size());
        n.resize(xs.size());
        for(int i = (int)xs.size() - 1; i >= 0; i--) {
            c[i] = 1;
            int j = upper_bound(xs.begin(), xs.end(), xs[i]+L) - xs.begin();
            if(j < xs.size()) {
                c[i] += c[j];
                n[i] = n[j];
            } else {
                n[i] = xs[i];
            }
        }
    }
};

vector<Bucket> bucket;

void build_bucket(bool f)
{
    vector<int> v;
    v.reserve(N);
    if(f) {
        for(int i = 0; i < N; i++)
            v.push_back(x[i]);
        sort(v.begin(), v.end());
    }
    else
        for(auto& b : bucket)
            for(auto i : b.xs)
                v.push_back(i);
    bucket.clear();
    for(int i = 0; i < N; i += B) {
        Bucket b;
        for(int j = i; j < i+B && j < N; j++) {
            b.xs.push_back(v[j]);
        }
        b.compute();
        bucket.push_back(b);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> L >> M;
    for(int i = 0; i < N; i++) cin >> x[i];

    build_bucket(1);
    while(M--) {
        if(M%B == 0) build_bucket(0);
        int i, y;
        cin >> i >> y;

        {
            int j = 0;
            while(j + 1 < bucket.size() && !binary_search(bucket[j].xs.begin(), bucket[j].xs.end(), x[i])) j++;
            bucket[j].erase(x[i]);
            bucket[j].compute();
        }
        x[i] = y;
        {
            int j = 0;
            while(j + 1 < bucket.size() && (bucket[j].xs.empty() || bucket[j].xs.back() <= x[i])) j++;
            bucket[j].add(x[i]);
            bucket[j].compute();
        }

        int ans = 0;
        int s = -1e9 - 5;
        for(auto& b : bucket) {
            int k = upper_bound(b.xs.begin(), b.xs.end(), s+L) - b.xs.begin();
            if(k >= b.xs.size()) continue;
            ans += b.c[k];
            s = b.n[k];
        }
        cout << ans << "\n";
    }
}