#include <bits/stdc++.h>

using namespace std;

const int MAXT = 3030;

int T, K;
double p[MAXT][MAXT], P[MAXT], E[MAXT];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> T >> K;
    T--;

    p[0][0] = 1;
    for(int i = 1; i < MAXT; i++) {
        p[i][0] = p[i][i] = 0.5f * p[i-1][0];
        for(int j = 1; j < i; j++) {
            p[i][j] = 0.5f * (p[i-1][j] + p[i-1][j-1]);
        }
    }

    for(int i = T; i >= 0; i--) {
        P[i] = P[i+1] + p[T][i];
        E[i] = E[i+1] + i * p[T][i];
    }

    double e = 0.5f * T;
    int progress = 1;
    while(true) {
        int k = floor(e) + 1;

        double a = 1.0f - P[k];
        double b = E[k];
        double alpha = b / (1.0f - a);

        double H1 = e - alpha;
        auto Xn = [&](int n) {
            return pow(a, n) * H1 + alpha;
        };
        
        int lo = 0;
        int hi = K;
        while(lo + 1 < hi) {
            int mid = (lo + hi) / 2;
            double p = Xn(mid);
            if(Xn(mid) <= k) lo = mid;
            else hi = mid;
        }
        if(progress + hi >= K) {
            e = Xn(K - progress);
            break;
        }
        progress += hi;
        e = Xn(hi);
    }
    cout << fixed << setprecision(16) << 1 + e << "\n";
}