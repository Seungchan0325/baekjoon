#pragma GCC optimize("O2")

#include <bits/stdc++.h>

using namespace std;

const int sz = 1<<30;

struct Node {
    int count, depth;
    Node *left, *right;
    Node(int dep) : count(0), depth(dep), left(nullptr), right(nullptr) {}
    ~Node()
    {
        if(left) delete left;
        if(right) delete right;
        left = right = nullptr;
    }

    void add(int x, int v)
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

    int find(int k, int s, int e)
    {
        if(s == e) return s^k;

        Node* l = (k&(1<<depth)) ? right : left;
        Node* r = (k&(1<<depth)) ? left : right;

        int m = (s + e) / 2;
        if(l != NULL && l->count) return l->find(k, s, m);
        else return r->find(k, m+1, e);
    }
};

const int MAXN = 202020;

int N, A[MAXN];
bool vst[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    Node* root = new Node(29);
    for(int i = 1; i <= N; i++) {
        cin >> A[i];
        root->add(A[i], 1);
    }

    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
    root->add(A[1], -1);
    if(root->count) {
        int x = root->find(A[1], 0, sz-1);
        pq.emplace(x^A[1], x, A[1]);
    }
    long long ans = 0;
    int cnt = 0;
    while(!pq.empty() && root->count) {
        auto [w, x, y] = pq.top(); pq.pop();
        if(root->count) {
            auto t = root->find(y, 0, sz-1);
            pq.emplace(t^y, t, y);
        }
        if(auto t = root->find(y, 0, sz-1); t != x) {
            cnt++;
            continue;
        }
        ans += w;
        root->add(x, -1);
        if(root->count) {
            auto t = root->find(x, 0, sz-1);
            pq.emplace(t^x, t, x);
        }
    }
    delete root;
    // cout << cnt << "\n";
    cout << ans;
}