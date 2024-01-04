#include <bits/stdc++.h>

using namespace std;

const int MAXN = 17;

int n, arr[MAXN];
double cache[1<<MAXN];

double dp(int taken) {
    double& ret = cache[taken];
    if(ret != -INFINITY) return ret;

    // for(int i = 0; i < 32; i++) {
    //     cout << ((taken & (1<<i)) ? 1 : 0);
    // }
    // cout << "\n";

    ret = 0.0;
    for(int i = 0; i < n; i++) {
        if(taken & (1<<i)) continue;
        for(int j = 0; j < n; j++) {
            if((taken & (1<<j)) || j == i) continue;
            for(int k = 0; k < n; k++) {
                if((taken & (1<<k)) || k == i || k == j) continue;

                vector<int> v = {arr[i], arr[j], arr[k]};
                sort(v.begin(), v.end());
                if(v[2] >= v[0] + v[1]) continue;

                double p = (v[0] + v[1] + v[2]) / 2.0;
                double area = sqrt(p * (p - v[0]) * (p - v[1]) * (p - v[2]));

                int next_taken = (taken | (1<<i) | (1<<j) | (1<<k));
                ret = max(area + dp(next_taken), ret);
            }
        }
    }

    return ret;
}

int main() {
    cin >> n;
    for(int i = 0; i < n; i++) cin >> arr[i];
    for(int i = 0; i < (1<<MAXN); i++) cache[i] = -INFINITY;

    double result = dp(0);
    cout.precision(10);
    cout << result;
}