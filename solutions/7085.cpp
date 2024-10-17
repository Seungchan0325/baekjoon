#include <bits/stdc++.h>

using namespace std;

const int MAXQ = 200005;

struct Qry {
    int x, y, idx, op, kth;
    bool operator < (const Qry& other) const
    {
        if(x == other.x) return y > other.y;
        return x > other.x;
    }
};

int Q, ans[MAXQ];
vector<int> X, Y;
Qry v[MAXQ];

void DnC(int s, int e)
{
    if(s == e) return;
    int m = (s + e) / 2;
    DnC(s, m);
    DnC(m+1, e);
    sort(v + s, v + m + 1);
    sort(v + m + 1, v + e + 1);
    int j = s;
    map<int, int> dots;
    for(int i = m+1; i <= e; i++) {
        for(; j <= m && v[j] < v[i]; j++) dots[v[j].y] = v[j].idx;
        if(v[i].op) {
            auto it = dots.lower_bound(v[i].y);
            if(it == dots.end()) {
                if(ans[v[i].kth] == 0) ans[v[i].kth] = -1;
            }
            else {
                if(ans[v[i].kth] <= 0) {
                    ans[v[i].kth] = it->second;
                }
                else {
                    int n = it->second;
                    int m = ans[v[i].kth];
                    if(Y[n-1] > Y[m-1]) swap(n, m);
                    else if(Y[n-1] == Y[m-1] && X[n-1] > X[m-1]) swap(n, m);
                    ans[v[i].kth] = n;
                }
            }
        }
    }
}

int main()
{
    cin >> Q;
    for(int i = 1; i <= Q; i++) {
        char c;
        cin >> c;
        if(c == 'D') {
            int x, y;
            cin >> x >> y;
            X.push_back(x);
            Y.push_back(y);
            v[i] = {x, y, (int)X.size(), 0, i};
        }
        else {
            int j;
            cin >> j;
            v[i] = {X[j-1], Y[j-1], j, 1, i};
        }
    }
    DnC(1, Q);
    for(int i = 1; i <= Q; i++) {
        if(ans[i]) {
            if(ans[i] < 0) cout << "NE\n";
            else cout << ans[i] << "\n";
        }
    }
}