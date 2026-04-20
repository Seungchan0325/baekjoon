#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 202020;

ll CX;

struct Circle {
    ll x, y, r, id, D, P, par;
    bool isQ;
} cx[MAXN];

struct Arc {
    Circle* c;
    bool upper;
    Arc(Circle* _c, bool _upper) : c(_c), upper(_upper) {}
    double eval(ll x) const {
        double dy = sqrt(c->r*c->r - (x-c->x)*(x-c->x));
        return upper ? c->y + dy : c->y - dy;
    }
    bool operator < (const Arc& arc) const {
        if(c->id == arc.c->id) {
            return upper < arc.upper;
        }
        return eval(CX) < arc.eval(CX);
    }
};

int n, q;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> q;
    for(int i = 1; i <= n; i++) {
        cin >> cx[i].x >> cx[i].y >> cx[i].r;
        cx[i].id = i;
        cx[i].D = 1;
    }
    for(int i = n+1; i <= n+q; i++) {
        cin >> cx[i].x >> cx[i].y >> cx[i].r;
        cx[i].id = i;
        cx[i].isQ = true;
    }

    vector<pair<int, int>> events;
    for(int i = 1; i <= n+q; i++) {
        events.push_back({cx[i].x-cx[i].r, i});
        events.push_back({cx[i].x+cx[i].r, -i});
    }
    sort(events.begin(), events.end());
    set<Arc> s;
    for(auto [x, i] : events) {
        CX = x;
        if(i > 0) {
            auto top = s.upper_bound(Arc(cx+i, true));
            if(top != s.end()) {
                cx[i].par = top->upper ? top->c->id : top->c->par;
            }

            s.insert(Arc(cx+i, true));
            s.insert(Arc(cx+i, false));
        } else {
            i = -i;
            int j = cx[i].par;
            if(cx[i].isQ) {
                cx[j].D += cx[i].D;
                cx[j].P += cx[i].P;
            } else {
                cx[j].D += cx[i].P;
                cx[j].P += max(cx[i].D, cx[i].P);
            }
            s.erase(Arc(cx+i, true));
            s.erase(Arc(cx+i, false));
        }
    }

    for(int i = n+1; i <= n+q; i++) {
        cout << max(cx[i].D+1, cx[i].P) << "\n";
    }
}
