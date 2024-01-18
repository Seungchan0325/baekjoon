#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9+1;
const int MAXN = 1000001;

bool is_in_x_axis(int px, int py, int x, int y) {
    return px == x && y <= 0 && 0 <= py;
}

bool is_out_x_axis(int px, int py, int x, int y) {
    return px == x && py <= 0 && 0 <= y;
}

int n, x[MAXN], y[MAXN];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n;
    for(int i=0; i<n; i++) cin>>x[i]>>y[i];

    int start, minL = INF;
    for(int i=0; i<n; i++)
        if(is_out_x_axis(x[i%n], y[i%n], x[(i+1)%n], y[(i+1)%n]))
            if(x[i] < minL) {
                start = i;
                minL = x[i];
            }
    
    int l, r;
    vector<pair<int, int>> lr;
    for(int i=start; i<n+start; i++) {
        int ni = i % n;
        int nj = (i + 1) % n;
        if(is_out_x_axis(x[ni], y[ni], x[nj], y[nj])) {
            l = x[ni];
        } else if(is_in_x_axis(x[ni], y[ni], x[nj], y[nj])) {
            r = x[ni];
            if(r < l) swap(l, r);

            lr.push_back({l, r});
        }
    }

    sort(lr.begin(), lr.end());

    int ch, leaf;
    ch = leaf = 0;
    stack<int> s;
    s.push(INF);

    for(int i=0; i<lr.size(); i++) {
        if(s.top() < lr[i].first) leaf++;
        while(s.top() < lr[i].first) s.pop();
        if(s.size() == 1) ch++;
        s.push(lr[i].second);
    }

    if(2 <= s.size()) leaf++;
    
    cout<<ch<<" "<<leaf;
}