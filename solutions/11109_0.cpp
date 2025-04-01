#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while(t--) {
        int d, n, s, p;
        cin >> d >> n >> s >> p;
        int a = n * s;
        int b = d + n * p;
        if(a == b) cout << "does not matter\n";
        if(a < b) cout << "do not parallelize\n";
        if(a > b) cout << "parallelize\n";
    }
}