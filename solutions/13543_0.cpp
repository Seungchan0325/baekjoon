#include <bits/stdc++.h>

using namespace std;

using uint = unsigned int;

const int MAXN = 101010;
const int B = 300;

uint bino[11][11];

struct Bucket {
    int s;
    int e;
    vector<uint> v;
    uint w[11] = {};
    void refresh()
    {
        for(int j = 0; j <= 10; j++) w[j] = 0;
        for(int i = 0; i < v.size(); i++) {
            uint x = 1;
            for(int j = 0; j <= 10; j++) {
                w[j] += x * v[i];
                x *= i+1;
            }
        }
    }
    void insert(int idx, uint x)
    {
        v.insert(v.begin()+idx-s, x);
        e++;
        refresh();
    }
    void del(int idx)
    {
        v.erase(v.begin()+idx-s);
        e--;
        refresh();
    }
    uint query(uint l, int k)
    {
        l -= s;
        uint ret = 0;
        uint x = 1;
        for(int i = k; i >= 0; i--) {
            ret += bino[k][i] * x * w[i];
            x *= -l;
        }
        return ret;
    }
    uint get(int idx)
    {
        return v[idx-s];
    }
};

int N, M;
vector<Bucket> bs;

uint pw(uint x, int n)
{
    uint res = 1;
    while(n) {
        if(n&1) res *= x;
        x *= x;
        n>>=1;
    }
    return res;
}

void init(vector<uint> v)
{
    int n = v.size();
    int m = (n+B-1) / B;
    bs.clear();
    bs.resize(m);
    for(int i = 0, j = 0; i < n; i+=B, j++) {
        bs[j].s = i;
        bs[j].v.reserve(B);
        for(int k = i; k < n && k < i+B; k++) {
            bs[j].v.push_back(v[k]);
        }
        bs[j].e = bs[j].s + ssize(bs[j].v) - 1;
        bs[j].refresh();
    }
}

void insert(int idx, uint x)
{
    int m = bs.size();
    for(int i = 0; i < m; i++) {
        if(bs[i].s <= idx && idx <= bs[i].e + 1) {
            bs[i].insert(idx, x);
            for(int j = i+1; j < m; j++) {
                bs[j].s++;
                bs[j].e++;
            }
            return;
        }
    }
}
void del(int idx)
{
    int m = bs.size();
    for(int i = 0; i < m; i++) {
        if(bs[i].s <= idx && idx <= bs[i].e) {
            bs[i].del(idx);
            for(int j = i+1; j < m; j++) {
                bs[j].s--;
                bs[j].e--;
            }
            return;
        }
    }
}

uint query(int l, int r, int k)
{
    int m = bs.size();
    uint res = 0;
    for(int i = 0; i < m; i++) {
        if(l <= bs[i].s && bs[i].e <= r) {
            res += bs[i].query(l, k);
        } else if(bs[i].s <= l && r <= bs[i].e) {
            for(int j = l; j <= r; j++) {
                res += bs[i].get(j) * pw(j-l+1, k);
            }
        } else if(bs[i].s <= l && bs[i].e <= r) {
            for(int j = l; j <= bs[i].e; j++) {
                res += bs[i].get(j) * pw(j-l+1, k);
            }
        } else if(l <= bs[i].s && r <= bs[i].e) {
            for(int j = bs[i].s; j <= r; j++) {
                res += bs[i].get(j) * pw(j-l+1, k);
            }
        }
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    for(int i = 0; i < 11; i++) {
        bino[i][0] = bino[i][i] = 1;
        for(int j = 1; j < i; j++) {
            bino[i][j] = bino[i-1][j] + bino[i-1][j-1];
        }
    }
    cin >> N;
    vector<uint> v(N);
    for(auto& i : v) cin >> i;
    init(v);
    cin >> M;
    while(M--) {
        if(M%B == 0) {
            vector<uint> v;
            int m = bs.size();
            for(int i = 0; i < m; i++) {
                v.insert(v.end(), bs[i].v.begin(), bs[i].v.end());
            }
            init(v);
        }
        int t;
        cin >> t;
        if(t == 1) {
            int p;
            uint v;
            cin >> p >> v;
            insert(p, v);
        } else if(t == 2) {
            int p;
            cin >> p;
            del(p);
        } else if(t == 3) {
            int p;
            uint v;
            cin >> p >> v;
            del(p);
            insert(p, v);
        } else if(t == 4) {
            int l, r, k;
            cin >> l >> r >> k;
            uint ans = query(l, r, k);
            cout << ans << "\n";
        }
    }
}