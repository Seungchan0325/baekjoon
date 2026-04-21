#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int long long

const int MAXN = 303030;

struct Circle {
    int x, y, r, id;
    bool doesIntersect(const Circle& rhs) const {
        ll dx = x - rhs.x;
        ll dy = y - rhs.y;
        ll pr = r + rhs.r;
        return dx * dx + dy * dy <= pr * pr;
    }
    bool operator < (int other) {
        return y < other;
    }
};

int n, a[MAXN];
Circle cx[MAXN];

int floorDiv(int a, int b)
{
    int q = a / b;
    if((a^b)<0&&q*b!=a)q--;
    return q;
}

signed main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> cx[i].x >> cx[i].y >> cx[i].r; cx[i].id = i;
    }

    auto rescale = [](int R, vector<int>& pos, vector<vector<Circle>>& grid) {
        vector<int> newPos;
        vector<vector<Circle>> newGrid;
        for(int i = 0; i < pos.size(); i++) {
            vector<Circle> left, right;
            for(auto c : grid[i]) {
                if(a[c.id]) continue;
                if(c.x <= pos[i]+R) left.push_back(c);
                if(c.x >= pos[i]+R) right.push_back(c);
            }
            if(left.size()) {
                newPos.push_back(pos[i]);
                newGrid.push_back(left);
            }
            if(right.size()) {
                newPos.push_back(pos[i]+R);
                newGrid.push_back(right);
            }
        }
        pos = newPos;
        grid = newGrid;
    };

    int R = 1<<30;

    vector<Circle> vc(cx+1, cx+n+1);
    sort(vc.begin(), vc.end(), [](const Circle& a, const Circle& b) { return tuple(-a.r, a.id) < tuple(-b.r, b.id); });

    vector<int> pos = {-(1<<30)};
    vector<vector<Circle>> grid = {vector<Circle>(cx+1, cx+n+1)};
    sort(grid[0].begin(), grid[0].end(), [](const Circle& a, const Circle& b) { return a.y < b.y; });
    rescale(R, pos, grid);

    for(auto ci : vc) {
        if(a[ci.id]) continue;
        a[ci.id] = ci.id;

        while((R>>1) >= cx[ci.id].r) {
            R>>=1;
            rescale(R, pos, grid);
        }

        int sx = lower_bound(pos.begin(), pos.end(), ci.x-2*ci.r-R) - pos.begin();
        for(int j = sx; j < pos.size(); j++) {
            if(pos[j] > ci.x+2*ci.r) break;
            int sy = lower_bound(grid[j].begin(), grid[j].end(), ci.y-2*ci.r) - grid[j].begin();
            for(int k = sy; k < grid[j].size(); k++) {
                auto cj = grid[j][k];
                if(cj.y > ci.y+2*ci.r) break;
                if(!a[cj.id] && ci.doesIntersect(cj)) a[cj.id] = ci.id;
            }
        }
    }

    for(int i = 1; i <= n; i++) cout << a[i] << " ";
}
