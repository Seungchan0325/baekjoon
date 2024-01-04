#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x;
    int y;
};

struct Circle {
    int x;
    int y;
    int r;
};

int t, n, cnt;
Point src, dst;
Circle planets[51];

bool isPointInCircle(Circle c, Point p) {
    int dist = (c.x - p.x) * (c.x - p.x) + (c.y - p.y) * (c.y - p.y);
    return dist <= c.r * c.r;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin>>t;
    while(t--) {
        cin>>src.x>>src.y>>dst.x>>dst.y;
        cin>>n;
        for(int i=0; i<n; i++)
            cin>>planets[i].x>>planets[i].y>>planets[i].r;
        
        sort(planets, planets + n, [](Circle c1, Circle c2) { return c1.r < c2.r; });

        cnt = 0;
        for(int i=0; i<n; i++) {
            bool isSrcInPlanet = isPointInCircle(planets[i], src);
            bool isDstInPlanet = isPointInCircle(planets[i], dst);

            if(isSrcInPlanet && isDstInPlanet) break;
            if(isSrcInPlanet || isDstInPlanet) cnt++;
        }

        cout<<cnt<<"\n";
    }
}