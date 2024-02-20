#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int MAXN = 300005;

bool chk[MAXN];
int n, a[MAXN], nxt[MAXN];
set<int> remains;
priority_queue<int, vector<int>, greater<int>> pq[MAXN];
set<pair<int, int>> s;

void pop(int idx)
{
    s.erase(make_pair(pq[idx].size(), idx));
    int v = pq[idx].top(); pq[idx].pop();
    cout << v + 1 << " ";
    chk[v] = true;
    remains.erase(v);
    s.insert(make_pair(pq[idx].size(), idx));
}

int main()
{
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        pq[a[i]].push(i);
        remains.insert(i);
    }

    int t = n;
    for(int i = n - 1; i >= 0; i--) {
        nxt[i] = t;
        if(a[i] != a[i-1]) t = i;
    }

    for(int i = 1; i <= n; i++) {
        if(pq[i].size() > (n + 1) / 2) {
            cout << "-1";
            return 0;
        }
        s.insert(make_pair(pq[i].size(), i));
    }

    int prv = 0;
    int iter = 0;
    for(int i = 0; i < n;) {
        if(chk[i]) { i++; continue; }
        int mx_sz = (n - iter) / 2;
        if(auto [sz, idx] = *s.rbegin(); sz > mx_sz) {
            prv = idx;
            pop(idx);
        } else {
            if(prv == a[i]) {
                auto it = remains.begin();
                while(a[*it] == prv) {
                    it = remains.lower_bound(nxt[*it]);
                }
                prv = a[*it];
                pop(a[*it]);
            } else {
                prv = a[i];
                pop(a[i]);
                i++;
            }
        }
        iter++;
    }

    return 0;
}