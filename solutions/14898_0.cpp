#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int MAXN = 1000005;
const int MAXQ = 1000005;

int N, Q, arr[MAXN], nxt[MAXN], prv[MAXN];
vector<int> tree[2*MAXN];

void init()
{
    for(int i = 0; i < N; i++) {
        tree[i+N].push_back(nxt[i]);
    }

    for(int i = N-1; i > 0; i--) {
        auto& L = tree[i<<1];
        auto& R = tree[i<<1|1];
        tree[i].resize(L.size() + R.size());
        merge(L.begin(), L.end(), R.begin(), R.end(), tree[i].begin());
    }
}

int query(int l, int r, int k)
{
    int ret = 0;
    for(l+=N, r+=N; l <= r; l>>=1, r>>=1) {
        if(l&1) {
            ret += tree[l].end() - upper_bound(tree[l].begin(), tree[l].end(), k);
            l++;
        }
        if(~r&1) {
            ret += tree[r].end() - upper_bound(tree[r].begin(), tree[r].end(), k);
            r--;
        }
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    vector<int> v(arr, arr + N);
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    fill_n(prv, v.size(), INF);
    for(int i = N-1; i >= 0; i--) {
        int idx = lower_bound(v.begin(), v.end(), arr[i]) - v.begin();
        nxt[i] = prv[idx];
        prv[idx] = i;
    }

    init();

    cin >> Q;
    int prvQ = 0;
    while(Q--) {
        int x, r;
        cin >> x >> r;
        int l = x + prvQ;
        int result = query(l - 1, r - 1, r - 1);
        cout << result << "\n";
        prvQ = result;
    }
}