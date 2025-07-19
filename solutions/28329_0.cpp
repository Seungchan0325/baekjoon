#include <bits/stdc++.h>

using namespace std;

const int ALPHABET = 26;
const int MAXN = 101010;

struct Node {
    int zeros;
    int ones;
    int mn;
};

Node merge(Node a, Node b)
{
    Node ret;
    ret.zeros = a.zeros + b.zeros;
    ret.ones = a.ones + b.ones;
    ret.mn = min({a.mn + b.zeros, a.ones + b.mn, a.ones + b.zeros});
    return ret;
}

int N, Q;
struct SegTree {
    Node tree[4*MAXN] = {};
    void update(int x, int v, int s=1, int e=N, int idx=1)
    {
        if(e < x || x < s) return;
        if(s == e) {
            tree[idx].zeros = (v == 0);
            tree[idx].ones = (v == 1);
            tree[idx].mn = 0;
            return;
        }
        int m = (s + e) / 2;
        update(x, v, s, m, 2*idx);
        update(x, v, m+1, e, 2*idx+1);
        tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
    }
};

SegTree seg[ALPHABET];
string S;

int get_ans()
{
    int ans = 0;
    for(int i = 0; i < 26; i++) {
        ans += seg[i].tree[1].mn;
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> S;
    N = S.size();
    S = ' ' + S;
    cin >> Q;

    for(int i = 1; i <= N; i++) {
        for(int j = 0; j <= S[i]-'a'; j++) seg[j].update(i, 1);
        for(int j = S[i]-'a'+1; j < 26; j++) seg[j].update(i, 0);
    }

    cout << get_ans() << "\n";

    while(Q--) {
        int i;
        char c;
        cin >> i >> c;
        for(int j = 0; j <= c-'a'; j++) seg[j].update(i, 1);
        for(int j = c-'a'+1; j < 26; j++) seg[j].update(i, 0);
        cout << get_ans() << "\n";
    }
}