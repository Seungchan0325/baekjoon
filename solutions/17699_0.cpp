#include <bits/stdc++.h>

using namespace std;

const int MAXN = 505050;

bool instack[MAXN];
int N, Q, C[MAXN], B[MAXN], L[MAXN], R[MAXN], pv, num[MAXN], low[MAXN], scc[MAXN];
vector<int> A[MAXN];
vector<int> tree[4*MAXN];
stack<int> s;

void build(int s = 1, int e = N, int idx = 1)
{
    if(s == e) {
        tree[idx] = A[s];
        return;
    }
    int m = (s + e) / 2;
    build(s, m, 2*idx);
    build(m+1, e, 2*idx+1);
    auto& l = tree[2*idx];
    auto& r = tree[2*idx+1];
    tree[idx].resize(l.size() + r.size());
    merge(l.begin(), l.end(), r.begin(), r.end(), tree[idx].begin());
}

bool query(int l, int r, int v, int s = 1, int e = N, int idx = 1)
{
    if(e < l || r < s) return false;
    if(l <= s && e <= r) return binary_search(tree[idx].begin(), tree[idx].end(), v);
    int m = (s + e) / 2;
    return query(l, r, v, s, m, 2*idx) || query(l, r, v, m+1, e, 2*idx+1);
}

void dp(int i)
{
    low[i] = num[i] = ++pv;
    instack[i] = true;
    s.push(i);
    while(num[i] >= low[i]) {
        bool done = true;
        if(L[i] > 1 && query(L[i], R[i], C[L[i]-1])) {
            done = false;
            if(!num[L[i]-1]) {
                dp(L[i]-1);
                low[i] = min(low[i], low[L[i]-1]);
            }
            else if(instack[L[i]-1]) low[i] = min(low[i], low[L[i]-1]);
            R[i] = max(R[i], R[L[i]-1]);
            L[i] = min(L[i], L[L[i]-1]);
        }
        if(R[i] < N && query(L[i], R[i], C[R[i]])) {
            done = false;
            if(!num[R[i]+1]) {
                dp(R[i]+1);
                low[i] = min(low[i], low[R[i]+1]);
            }
            else if(instack[R[i]+1]) low[i] = min(low[i], low[R[i]+1]);
            L[i] = min(L[i], L[R[i]+1]);
            R[i] = max(R[i], R[R[i]+1]);
        }
        if(done) break;
    }

    if(low[i] == num[i]) {
        while(s.top() != i) {
            scc[s.top()] = i;
            instack[s.top()] = false;
            s.pop();
        }
        scc[s.top()] = i;
        instack[s.top()] = false;
        s.pop();
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N;
    for(int i = 1; i < N; i++) cin >> C[i];
    for(int i = 1; i <= N; i++) {
        cin >> B[i];
        A[i].resize(B[i]);
        for(auto& j : A[i]) cin >> j;
        sort(A[i].begin(), A[i].end());
    }

    for(int i = 1; i <= N; i++) L[i] = R[i] = i;

    build();

    for(int i = 1; i <= N; i++) {
        if(!num[i]) dp(i);
    }

    cin >> Q;
    while(Q--) {
        int x, y; cin >> x >> y;
        x = scc[x];
        if(L[x] <= y && y <= R[x]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}