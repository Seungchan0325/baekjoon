#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

int N, A[MAXN], M, OP[MAXN], I[MAXN], J[MAXN], K[MAXN];
vector<int> vs;

struct Fenwick
{
    int n;
    vector<int> tree;
    void init(int _n)
    {
        n = _n;
        tree.resize(n+1);
    }
    void update(int x, int v)
    {
        while(x <= n) {
            tree[x] += v;
            x += x & -x;
        }
    }
    int query(int x)
    {
        int ret = 0;
        while(x > 0) {
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i];
    cin >> M;
    for(int i = 1; i <= M; i++) {
        cin >> OP[i];
        if(OP[i] == 1) cin >> I[i] >> J[i] >> K[i];
        else cin >> I[i] >> K[i];
    }

    for(int i = 1; i <= N; i++) vs.push_back(A[i]);
    for(int i = 1; i <= M; i++) vs.push_back(K[i]);
    sort(vs.begin(), vs.end());
    vs.erase(unique(vs.begin(), vs.end()), vs.end());

    int sqrtN = sqrt(N);
    vector<Fenwick> bucket(sqrtN+5);
    for(auto&b : bucket) b.init(vs.size() + 5);
    auto update = [&](int x, int v, int d) {
        int idx = lower_bound(vs.begin(), vs.end(), A[x]) - vs.begin() + 1;
        bucket[x/sqrtN].update(idx, d);
    };
    for(int i = 1; i <= N; i++) update(i, A[i], 1);

    for(int i = 1; i <= M; i++) {
        if(OP[i] == 2) {
            update(I[i], A[I[i]], -1);
            A[I[i]] = K[i];
            update(I[i], A[I[i]], 1);
        } else {
            int ans = 0;
            int l = (I[i] + sqrtN - 1) / sqrtN;
            int r = J[i] / sqrtN;
            int idx = lower_bound(vs.begin(), vs.end(), K[i]) - vs.begin() + 1;
            for(int i = l; i < r; i++) ans += bucket[i].query(vs.size()+1) - bucket[i].query(idx);

            if(r < l) {
                l = I[i]-1;
                r = I[i];
            } else {
                l *= sqrtN; l--;
                r *= sqrtN;
            }
            while(I[i] <= l) {
                if(A[l] > K[i]) ans++;
                l--;
            }
            while(r <= J[i]) {
                if(A[r] > K[i]) ans++;
                r++;
            }
            cout << ans << "\n";
        }
    }
}