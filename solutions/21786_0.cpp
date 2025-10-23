#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 250505;

struct Node {
    ll smx;
    ll sum;
    ll neg;
    int start;
};

Node merge(Node a, Node b)
{
    if(a.smx + b.sum > b.smx) {
        return {a.smx+b.sum, a.sum+b.sum, a.neg+b.neg, a.start};
    } else {
        return {b.smx, a.sum+b.sum, a.neg+b.neg, b.start};
    }
}

int N, M, Q;
Node tree[2*MAXN];
ll T[MAXN], L[MAXN], R[MAXN], C[MAXN], K[MAXN], A[MAXN], B[MAXN], ans[MAXN];
vector<int> qrys[MAXN];

void build()
{
    for(int i = 0; i < MAXN; i++) tree[i+MAXN].start = i;
    for(int i = MAXN-1; i >= 0; i--) tree[i] = merge(tree[i<<1], tree[i<<1|1]);
}

void update(int x, ll v)
{
    x += MAXN;
    tree[x].sum += v;
    tree[x].smx = max<ll>(tree[x].sum, 0);
    if(tree[x].sum < 0) tree[x].neg += v;
    else tree[x].neg = 0;
    while(x>>=1) tree[x] = merge(tree[x<<1], tree[x<<1|1]);
}

Node query(int l, int r)
{
    Node lef = {}, rig = {};
    for(l+=MAXN,r+=MAXN; l<=r; l>>=1,r>>=1) {
        if(l&1) lef = merge(lef, tree[l++]);
        if(~r&1) rig = merge(tree[r--], rig);
    }
    return merge(lef, rig);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M >> Q;
    vector<int> lef, rig;
    for(int i = 1; i <= Q; i++) {
        cin >> T[i];
        if(T[i] == 1) {
            cin >> L[i] >> R[i] >> C[i] >> K[i];
            lef.push_back(i); rig.push_back(i);
        } else if(T[i] == 2) {
            cin >> L[i] >> R[i] >> K[i]; K[i] = -K[i];
            lef.push_back(i); rig.push_back(i);
        } else {
            cin >> A[i] >> B[i];
            qrys[A[i]].push_back(i);
        }
    }
    sort(lef.begin(), lef.end(), [](int i, int j) {return L[i] < L[j];});
    sort(rig.begin(), rig.end(), [](int i, int j) {return R[i] < R[j];});
    int p, q;
    p = q = 0;
    build();
    for(int i = 1; i <= N; i++) {
        while(p < lef.size() && L[lef[p]] <= i) {
            update(lef[p], K[lef[p]]);
            p++;
        }
        while(q < rig.size() && R[rig[q]] < i) {
            update(rig[q], -K[rig[q]]);
            q++;
        }

        for(int j : qrys[i]) {
            Node nd = query(1, j);
            int start = nd.start;
            ll sz = nd.smx;
            if(B[j] > sz) {
                ans[j] = 0;
                continue;
            }

            int lo, hi;
            lo = start-1;
            hi = j;
            while(lo+1 < hi) {
                int mid = (lo + hi) / 2;
                if(query(start, mid).smx + query(mid+1, j).neg < B[j]) lo = mid;
                else hi = mid;
            }

            ans[j] = C[hi];
        }
    }

    for(int i = 1; i <= Q; i++) {
        if(T[i] == 3) cout << ans[i] << "\n";
    }
}