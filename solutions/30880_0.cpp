#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 250005;
const ll MOD = 1e9 + 7;
const string ROCK = "ROCK";

struct T {
    int sz;
    ll cnt[5];
    ll rock[5][5];

    void init()
    {
        sz = 0;
        memset(cnt, 0, sizeof(cnt));
        memset(rock, 0, sizeof(rock));
        for(int i = 0; i < 5; i++) rock[i][i] = 1;
    }

    T()
    {
        init();
    }
};

int N, Q;
char s[MAXN];
ll sq[MAXN];
T tree[4*MAXN];

void merge(const T& a, const T& b, T& c)
{
    c.init();

    if(a.sz == 0) {
        c = b;
        return;
    }
    if(b.sz == 0) {
        c = a;
        return;
    }

    c.sz = a.sz + b.sz;
    int s = 0;
    for(int e = s + 1; e <= ROCK.size(); e++) {
        for(int m = s; m <= e; m++) {
            c.rock[s][e] += (a.rock[s][m] * b.rock[m][e]) % MOD;
            c.rock[s][e] %= MOD;
            if(a.rock[s][m] > 0 && b.rock[m][e] > 0) {
                if(m == 0) {
                    c.cnt[e] += (sq[a.sz] * b.cnt[e]) % MOD;
                    c.cnt[e] %= MOD;
                } else {
                    c.cnt[e] += (a.cnt[m] * b.rock[m][e]) % MOD;
                    c.cnt[e] %= MOD;
                }
            }
        }
    }

    for(s = 1; s < ROCK.size(); s++) {
        for(int e = s + 1; e <= ROCK.size(); e++) {
            for(int m = s; m <= e; m++) {
                c.rock[s][e] += (a.rock[s][m] * b.rock[m][e]) % MOD;
                c.rock[s][e] %= MOD;
            }
        }
    }
}

void update(int pos, char c, int s = 1, int e = N, int idx = 1)
{
    if(e < pos || pos < s) return;

    if(s == e) {
        tree[idx].init();
        tree[idx].sz = 1;
        int i = ROCK.find(c);
        if(i == 0) tree[idx].cnt[1] = 1;
        if(i != -1) tree[idx].rock[i][i+1] = 1;
        return;
    }

    int m = (s + e) / 2;
    update(pos, c, s, m, 2*idx);
    update(pos, c, m+1, e, 2*idx+1);
    merge(tree[2*idx], tree[2*idx+1], tree[idx]);
}

T query(int l, int r, int s = 1, int e = N, int idx = 1)
{
    if(r < s || e < l) return T();
    if(l <= s && e <= r) return tree[idx];
    int m = (s + e) / 2;
    T ret; merge(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1), ret);
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    sq[0] = 1;
    for(int i = 1; i < MAXN; i++) {
        sq[i] = (2 * sq[i-1]) % MOD;
    }

    cin >> N;
    cin >> s;
    for(int i = 0; i < N; i++) {
        update(i+1, s[i]);
    }

    cin >> Q;
    while(Q--) {
        int t;
        cin >> t;
        if(t == 1) {
            int idx; char c; cin >> idx >> c;
            update(idx, c);
        } else {
            int l, r; cin >> l >> r;
            T result = query(l, r);
            cout << result.cnt[ROCK.size()] << "\n";
        }
    }
}