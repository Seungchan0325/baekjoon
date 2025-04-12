#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll sz = INT_MAX;
// const ll sz = 1023;

struct Node {
    ll count, depth;
    Node *left, *right;
    Node(ll dep) : count(0), depth(dep), left(nullptr), right(nullptr) {}
    ~Node()
    {
        if(left) delete left;
        if(right) delete right;
        left = right = nullptr;
    }

    void add(ll x, ll v)
    {
        if(depth == -1) {
            count += v;
            return;
        }

        if(~x & (1<<depth)) {
            if(!left) left = new Node(depth - 1);
            left->add(x, v);
        } else {
            if(!right) right = new Node(depth - 1);
            right->add(x, v);
        }

        count = 0;
        if(left) count += left->count;
        if(right) count += right->count;
    }

    ll find(ll k, ll x, ll s, ll e)
    {
        if(s == e) return s;

        Node* l = (x&(1<<depth)) ? right : left;
        Node* r = (x&(1<<depth)) ? left : right;

        ll m = (s + e) / 2;
        if(l != NULL && k <= l->count) return l->find(k, x, s, m);
        else return r->find(k - (l != NULL ? l->count : 0), x, m+1, e);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    ll n;
    cin >> n;
    vector<ll> v(n);

    Node* root = new Node(30);
    for(auto&i:v)cin>>i, root->add(i, 1);
    ll q;
    cin >> q;
    while(q--) {
        ll op, i, x;
        cin >> op >> i >> x;
        if(op == 1) {
            root->add(v[i-1], -1);
            v[i-1] = x;
            root->add(v[i-1], 1);
        } else {
            ll ans = root->find(n - i + 1, x, 0, sz);
            cout << ans << "\n";
        }
    }
}