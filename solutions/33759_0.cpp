#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD = 998'244'353;

struct Node
{
    Node() {}
    Node(char c)
    {
        if(c == '1' || c == '?') cnt[8] = 1;
        if(c == '0' || c == '?') cnt[9] = 1;
    }
    ll cnt[10] = {0, };
};

ll add(ll a, ll b)
{
    return ((a + b) % MOD + MOD) % MOD;
}

ll sub(ll a, ll b)
{
    return ((a - b) % MOD + MOD) % MOD;
}

ll mul(ll a, ll b)
{
    return (a * b % MOD + MOD) % MOD;
}

int And[10][10], Or[10][10];

Node merge(Node a, Node b, char op)
{
    Node ret;
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            if(op == '&' || op == '?') ret.cnt[And[i][j]] = add(ret.cnt[And[i][j]], mul(a.cnt[i], b.cnt[j]));
            if(op == '|' || op == '?') ret.cnt[Or[i][j]] = add(ret.cnt[Or[i][j]], mul(a.cnt[i], b.cnt[j]));
        }
    }
    return ret;
}

struct SegTree {
    int n, m;
    vector<char> opi;
    vector<int> ropi;
    vector<Node> tree;
    void _init(int s, int e, int idx, string& formula, int& i)
    {
        if(s == e) {
            tree[idx] = Node(formula[i]);
            opi[idx] = i;
            ropi[i] = idx;
            i++;
            return;
        }
        int m = (s + e) / 2;
        _init(s, m, 2*idx, formula, i);
        opi[idx] = formula[i];
        ropi[i] = idx;
        i++;
        _init(m+1, e, 2*idx+1, formula, i);
        tree[idx] = merge(tree[2*idx], tree[2*idx+1], opi[idx]);
    }

    void init(string formula)
    {
        n = (formula.size()+1) / 2;
        m = formula.size();
        tree.resize(4*n);
        opi.resize(4*n);
        ropi.resize(m);
        int i = 0;
        _init(0, n-1, 1, formula, i);
    }

    void update(int x, char v)
    {
        int idx = ropi[x];
        opi[idx] = v;
        if(~x&1) {
            tree[idx] = Node(v);
            idx /= 2;
        }
        while(idx > 0) {
            tree[idx] = merge(tree[2*idx], tree[2*idx+1], opi[idx]);
            idx /= 2;
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            int k = 0;
            k |= i&1;
            k |= j&4;
            k |= (i|j)&2;
            if((i&4) && (j&1)) k|=2;
            And[i][j] = k;
        }
    }
    for(int i = 0; i < 8; i++) And[i][8] = (i&4)|(i&~4);
    for(int i = 0; i < 8; i++) And[i][9] = (i&~4);
    for(int j = 0; j < 8; j++) And[8][j] = (j&1)|(j&~1);
    for(int j = 0; j < 8; j++) And[9][j] = ~1&j;
    And[8][8] = 8;
    And[8][9] = 9;
    And[9][8] = 9;
    And[9][9] = 9;

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            int k = 0;
            k |= i&1;
            k |= j&4;
            k |= (i|j)&2;
            if((i&4) || (j&1)) k|=2;
            Or[i][j] = k;
        }
    }
    for(int i = 0; i < 8; i++) Or[i][8] = 4|(i|((i&4)>>1));
    for(int i = 0; i < 8; i++) Or[i][9] = ~4&(i|((i&4)>>1));
    for(int j = 0; j < 8; j++) Or[8][j] = 1|(j|((j&1)<<1));
    for(int j = 0; j < 8; j++) Or[9][j] = ~1&(j|((j&1)<<1));
    Or[8][8] = 5;
    Or[8][9] = 1;
    Or[9][8] = 4;
    Or[9][9] = 0;

    int T;
    cin >> T;
    while(T--) {
        int N, Q;
        cin >> N >> Q;
        string formula;
        cin >> formula;
        SegTree sg;
        sg.init(formula);
        {
            auto t = sg.tree[1];
            ll ans = 0;
            for(int i = 0; i < 10; i++) ans = add(ans, t.cnt[i]);
            ans = sub(ans, t.cnt[0]);
            ans = sub(ans, t.cnt[9]);
            cout << ans << " ";
        }
        while(Q--) {
            int k;
            char c;
            cin >> k >> c;
            k--;
            sg.update(k, c);
            auto t = sg.tree[1];
            ll ans = 0;
            for(int i = 0; i < 10; i++) ans = add(ans, t.cnt[i]);
            ans = sub(ans, t.cnt[0]);
            ans = sub(ans, t.cnt[9]);
            cout << ans << " ";
        }
        cout << "\n";
    }
}