#include <bits/stdc++.h>

using namespace std;

#define X first
#define Y second

using ll = long long;
using pii = pair<ll, ll>;

ll ccw(pii p1, pii p2, pii p3)
{
    ll ret = (p2.X - p1.X) * (p3.Y - p1.Y) - (p3.X - p1.X) * (p2.Y - p1.Y);
    if(ret < 0) return -1;
    else if(ret == 0) return 0;
    else return 1;
}

int main()
{
    int N;
    cin >> N;
    vector<pii> v(N);
    for(auto& [x, y] : v) cin >> x >> y;

    for(int i = 0; i < 3; i++) {
        pii s;
        cin >> s.X >> s.Y;

        int cnt = 0;

        for(int i = 0; i < N; i++) {
            pii p1 = v[i];
            pii p2 = v[(i+1)%N];

            // 한 직선 위에 있음
            if(ccw(p1, p2, s) == 0) {
                if(p1 > p2) swap(p1, p2);
                if(p1 <= s && s <= p2) {
                    cnt = 1;
                    break;
                }
                continue;
            }

            if(p1.Y < p2.Y) swap(p1, p2);
            
            // 선분의 꼭짓점과 만남
            if(s.X < p1.X && s.Y == p1.Y) {
                cnt++;
                continue;
            }

            pii normal = {s.X+1, s.Y};

            if(ccw(s, normal, p1) == 0 || ccw(s, normal, p2) == 0) continue;

            ll p = ccw(s, normal, p1) * ccw(s, normal, p2);
            ll q = ccw(p1, p2, s);

            if(p < 0 && q < 0) cnt++;
        }

        cout << (cnt&1) << "\n";
    }
}