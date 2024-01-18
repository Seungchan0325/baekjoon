#include <iostream>
#include <algorithm>

using namespace std;

int n, m;
int x[51], y[51];

int main() {
    cin>>n>>m;
    
    for(int i=0; i<n; i++) {
        cin>>x[i];
    }
    for(int i=1; i<m; i++) {
        cin>>y[i];
    }
    y[0] = x[n-1];

    int x_min_idx = min_element(x, x+n) - x;
    int y_min_idx = min_element(y, y+m) - y;

    cout<<x_min_idx+1<<" "<<y_min_idx+1;
}