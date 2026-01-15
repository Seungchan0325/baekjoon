#include <bits/stdc++.h>

using namespace std;

const int MAXN = 404040;
const int inf = 1e9;

struct Seg {
    int tree[2*MAXN];
    void init()
    {
        for(int i = 0; i < MAXN; i++) {
            tree[i] = tree[i+MAXN] = inf;
        }
    }
    void update(int x, int v)
    {
        tree[x+=MAXN] = v;
        while(x>>=1) tree[x] = min(tree[x<<1], tree[x<<1|1]);
    }
    int query(int l, int r)
    {
        int res = inf;
        for(l+=MAXN, r+=MAXN; l<=r; l>>=1,r>>=1) {
            if(l&1) res = min(res, tree[l++]);
            if(~r&1) res = min(res, tree[r--]);
        }
        return res;
    }
};

int T, K, N, A[MAXN], B[MAXN], chk[MAXN];
int a[MAXN], b[MAXN], root[MAXN], idxa[MAXN], idxb[MAXN];
int low[MAXN], num[MAXN], pv;
vector<int> g[MAXN];
vector<pair<int, int>> bridges;
Seg sega, segb;

void dfs(int u, int p)
{
    low[u] = num[u] = ++pv;
    int pe = 0;
    for(auto v : g[u]) {
        if(v == p && !pe) {
            pe++;
            continue;
        }
        if(!num[v]) {
            root[v] = root[u];
            dfs(v, u);
            a[u] += a[v];
            b[u] += b[v];
            if(num[u] < low[v]) bridges.push_back({u, v});
            low[u] = min(low[u], low[v]);
        } else {
            low[u] = min(low[u], num[v]);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> T >> K;
    sega.init();
    segb.init();
    while(T--) {
        cin >> N;
        
        pv = 0;
        bridges.clear();
        for(int i = 1; i <= N; i++) {
            a[i] = 1; b[i] = 0;
            a[i+N] = 0; b[i+N] = 1;
        }
        for(int i = 1; i <= 2*N; i++) {
            g[i].clear();
            num[i] = low[i] = 0;
            root[i] = -1;
            chk[i] = false;
            idxa[i] = idxb[i] = 0;
        }
        for(int i = 0; i < 2*N; i++) {
            sega.update(i, inf);
            segb.update(i, inf);
        }
        
        for(int i = 1; i <= N; i++) cin >> A[i];
        for(int i = 1; i <= N; i++) cin >> B[i];
        for(int i = 1; i <= N; i++) B[i] += N;

        int cnt = 0;
        for(int i = 1; i <= N; i++) {
            if(!chk[A[i]]) cnt++, chk[A[i]] = true;
            if(!chk[B[i]]) cnt++, chk[B[i]] = true;
        }

        for(int i = 1; i <= N; i++) {
            g[A[i]].push_back(B[i]);
            g[B[i]].push_back(A[i]);
        }

        int ans = 0;
        for(int i = 1; i <= 2*N; i++) {
            if(root[i] == -1) {
                root[i] = i;
                dfs(i, -1);
                ans += min(a[i], b[i]);
            }
        }

        int singlea = 0;
        int singleb = 0;
        vector<array<int, 3>> va, vb;
        for(int i = 1; i <= 2*N; i++) {
            if(root[i] == i) {
                if(a[i] && b[i]) {
                    if(K == 2) {
                        va.push_back({a[i]-b[i], -a[i]+min(a[i], b[i]), i});
                        vb.push_back({b[i]-a[i], -b[i]+min(a[i], b[i]), i});
                    } else {
                        va.push_back({a[i]-b[i], a[i]-min(a[i], b[i]), i});
                        vb.push_back({b[i]-a[i], b[i]-min(a[i], b[i]), i});
                    }
                }
                else if(a[i]) singlea++;
                else singleb++;
            }
        }
        sort(va.begin(), va.end());
        sort(vb.begin(), vb.end());
        for(int i = 0; i < va.size(); i++) {
            idxa[va[i][2]] = i;
            sega.update(i, va[i][1]);
        }
        for(int i = 0; i < vb.size(); i++) {
            idxb[vb[i][2]] = i;
            segb.update(i, vb[i][1]);
        }

        sort(bridges.begin(), bridges.end());
        if(K == 1) {
            int mn = 0;
            for(auto [i, j] : bridges) {
                int ai = a[root[i]] - a[j];
                int bi = b[root[i]] - b[j];
                int aj = a[j];
                int bj = b[j];

                if(!(ai+aj == 1 && bi+bj == 1)) mn = min(min(ai, bi)+min(aj, bj)-min(ai+aj, bi+bj), mn);

                sega.update(idxa[root[i]], inf);
                segb.update(idxb[root[i]], inf);
                int x = lower_bound(va.begin(), va.end(), array<int, 3>{bi-ai, inf, inf}) - va.begin() - 1;
                int y = lower_bound(vb.begin(), vb.end(), array<int, 3>{ai-bi, inf, inf}) - vb.begin() - 1;
                mn = min(ai + sega.query(0, x) + min(aj, bj) - min(ai+aj, bi+bj), mn);
                mn = min(bi + segb.query(0, y) + min(aj, bj) - min(ai+aj, bi+bj), mn);
                
                x = lower_bound(va.begin(), va.end(), array<int, 3>{bj-aj, inf, inf}) - va.begin() - 1;
                y = lower_bound(vb.begin(), vb.end(), array<int, 3>{aj-bj, inf, inf}) - vb.begin() - 1;
                mn = min(aj + sega.query(0, x) + min(ai, bi) - min(ai+aj, bi+bj), mn);
                mn = min(bj + segb.query(0, y) + min(ai, bi) - min(ai+aj, bi+bj), mn);

                sega.update(idxa[root[i]], va[idxa[root[i]]][1]);
                segb.update(idxb[root[i]], vb[idxb[root[i]]][1]);

                if(i <= N && singleb) mn = min(min(ai, bi+1) + min(aj, bj) - min(ai+aj, bi+bj), mn);
                else if(i > N && singlea) mn = min(min(ai+1, bi) + min(aj, bj) - min(ai+aj, bi+bj), mn);

                if(j <= N && singleb) mn = min(min(aj, bj+1) + min(ai, bi) - min(ai+aj, bi+bj), mn);
                else if(j > N && singlea) mn = min(min(aj+1, bj) + min(ai, bi) - min(ai+aj, bi+bj), mn);
            }
            ans += mn;
        } else if(K == 2) {
            int mx = 0;
            for(int i = 1; i <= N; i++) {
                bool is_bridge = false;
                if(binary_search(bridges.begin(), bridges.end(), pair(A[i], B[i]))) is_bridge = true;
                if(binary_search(bridges.begin(), bridges.end(), pair(B[i], A[i]))) is_bridge = true;
                if(is_bridge) continue;

                int ai = a[root[A[i]]];
                int bi = b[root[A[i]]];
                
                sega.update(idxa[root[A[i]]], inf);
                segb.update(idxb[root[A[i]]], inf);
                int x = lower_bound(va.begin(), va.end(), array<int, 3>{bi-ai, inf, inf}) - va.begin() - 1;
                int y = lower_bound(vb.begin(), vb.end(), array<int, 3>{ai-bi, inf, inf}) - vb.begin() - 1;
                mx = max(ai - sega.query(0, x) - min(ai, bi), mx);
                mx = max(bi - segb.query(0, y) - min(ai, bi), mx);
                sega.update(idxa[root[A[i]]], va[idxa[root[A[i]]]][1]);
                segb.update(idxb[root[A[i]]], vb[idxb[root[A[i]]]][1]);

                
                if(singleb) mx = max(min(ai, bi+1) - min(ai, bi), mx);
                if(singlea) mx = max(min(ai+1, bi) - min(ai, bi), mx);
            }
            
            for(auto [i, j] : bridges) {
                int ai = a[root[i]] - a[j];
                int bi = b[root[i]] - b[j];
                int aj = a[j];
                int bj = b[j];

                if(!(ai+aj == 1 && bi+bj == 1)) mx = max(min(ai, bi)+min(aj, bj)-min(ai+aj, bi+bj), mx);

                sega.update(idxa[root[i]], inf);
                segb.update(idxb[root[i]], inf);
                int x = lower_bound(va.begin(), va.end(), array<int, 3>{bi-ai, inf, inf}) - va.begin() - 1;
                int y = lower_bound(vb.begin(), vb.end(), array<int, 3>{ai-bi, inf, inf}) - vb.begin() - 1;
                mx = max(ai - sega.query(0, x) + min(aj, bj) - min(ai+aj, bi+bj), mx);
                mx = max(bi - segb.query(0, y) + min(aj, bj) - min(ai+aj, bi+bj), mx);
                
                x = lower_bound(va.begin(), va.end(), array<int, 3>{bj-aj, inf, inf}) - va.begin() - 1;
                y = lower_bound(vb.begin(), vb.end(), array<int, 3>{aj-bj, inf, inf}) - vb.begin() - 1;
                mx = max(aj - sega.query(0, x) + min(ai, bi) - min(ai+aj, bi+bj), mx);
                mx = max(bj - segb.query(0, y) + min(ai, bi) - min(ai+aj, bi+bj), mx);

                sega.update(idxa[root[i]], va[idxa[root[i]]][1]);
                segb.update(idxb[root[i]], vb[idxb[root[i]]][1]);

                if(i <= N && singleb) mx = max(min(ai, bi+1) + min(aj, bj) - min(ai+aj, bi+bj), mx);
                else if(i > N && singlea) mx = max(min(ai+1, bi) + min(aj, bj) - min(ai+aj, bi+bj), mx);

                if(j <= N && singleb) mx = max(min(aj, bj+1) + min(ai, bi) - min(ai+aj, bi+bj), mx);
                else if(j > N && singlea) mx = max(min(aj+1, bj) + min(ai, bi) - min(ai+aj, bi+bj), mx);
            }
            ans += mx;
        }
        cout << ans << "\n";
    }
}