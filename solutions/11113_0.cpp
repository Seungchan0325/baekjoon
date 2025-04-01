#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<double> x(n), y(n);
    for(int i = 0; i < n; i++) cin >> x[i] >> y[i];
    int m;
    cin >> m;
    while(m--) {
        int c; cin >> c;
        double acc = 0;
        vector<int> path(c);
        for(auto& i : path) cin >> i;
        for(int i = 1; i < c; i++) {
            int p = path[i-1];
            int q = path[i];
            acc += sqrt((x[p] - x[q])*(x[p]-x[q]) + (y[p]-y[q])*(y[p]-y[q]));
        }
        cout << round(acc) << "\n";
    }    
}