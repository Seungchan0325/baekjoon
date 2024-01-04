#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e3+5;

int n;
int px[MAXN], py[MAXN];

int distance(int x1, int y1, int x2, int y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int main() {
    cin>>n;
    for(int i=0; i<n; i++) cin>>px[i]>>py[i];

    int i1 = -1;
    int min_dist = 1e9;
    for(int i=0; i<n; i++) {
        int max_dist = -1;
        int max_idx = -1;
        for(int j=0; j<n; j++) {
            int dist = distance(px[i], py[i], px[j], py[j]);
            if(max_dist < dist) {
                max_dist = dist;
                max_idx = i;
            }
        }
        if(max_dist < min_dist) {
            min_dist = max_dist;
            i1 = max_idx;
        }
    }

    cout<<px[i1]<<" "<<py[i1];
}