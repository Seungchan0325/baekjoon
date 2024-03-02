#include <bits/stdc++.h>

using namespace std;

int main()
{
    int A, B, C;
    cin >> A >> B >> C;

    double lo = 0, hi = 100005;
    for(int i = 0; i < 100; i++) {
        double mid = (lo + hi) / 2;
        if(A*mid + B*sin(mid) < C) lo = mid;
        else hi = mid;
    }

    printf("%.10f", lo);
}