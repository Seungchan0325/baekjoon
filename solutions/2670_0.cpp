#include <bits/stdc++.h>

using namespace std;

int N;
double a[10005];

int main()
{
    cin >> N;
    for(int i = 0; i < N; i++) {
        cin >> a[i];
    }

    double ans = -INFINITY;
    for(int i = 0; i < N; i++) {
        double b = a[i];
        ans = max(b, ans);
        for(int j = i + 1; j < N; j++) {
            b *= a[j];
            ans = max(b, ans);
        }
    }
    printf("%.3f", round(1000*ans)/1000);
}