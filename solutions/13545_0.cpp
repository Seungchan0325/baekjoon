#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;
const int B = 300;

struct Query {
    int i, j, idx;
    auto operator <=> (const Query& rhs) const {
        if(i / B != rhs.i / B) return i/B <=> rhs.i/B;
        return j <=> rhs.j;
    }
};

int N, Q, A[MAXN], ans[MAXN], cnt[MAXN], mx;
Query P[MAXN];
deque<int> dq[MAXN<<1];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i];
    A[0] = MAXN;
    for(int i = 1; i <= N; i++) A[i] += A[i-1];
    cin >> Q;
    for(int i = 1; i <= Q; i++) {
        cin >> P[i].i >> P[i].j; P[i].i--;
        P[i].idx = i;
    }
    sort(P+1, P+Q+1);

    auto push = [&](int i, int v) {
        if(dq[i].size()) {
            cnt[dq[i].back()-dq[i].front()] += v;
            if(v > 0) mx = max(mx, dq[i].back()-dq[i].front());
        }
    };

    int l = 1;
    int r = 0;
    cnt[0] = 1;
    for(int i = 1; i <= Q; i++) {
        while(P[i].i < l) {
            l--;
            push(A[l], -1);
            dq[A[l]].push_front(l);
            push(A[l], 1);
        }
        while(r < P[i].j) {
            r++;
            push(A[r], -1);
            dq[A[r]].push_back(r);
            push(A[r], 1);
        }
        while(l < P[i].i) {
            push(A[l], -1);
            dq[A[l]].pop_front();
            push(A[l], 1);
            l++;
        }
        while(P[i].j < r) {
            push(A[r], -1);
            dq[A[r]].pop_back();
            push(A[r], 1);
            r--;
        }
        while(!cnt[mx]) mx--;
        ans[P[i].idx] = mx;
    }
    
    for(int i = 1; i <= Q; i++) cout << ans[i] << "\n";
}