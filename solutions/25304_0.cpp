#include <bits/stdc++.h>

using namespace std;

int main()
{
    int sum, n;
    cin >> sum;
    cin >> n;
    int receipt = 0;
    for(int i = 0; i < n; i++) {
        int a, t;
        cin >> a >> t;
        receipt += a * t;
    }
    cout << (char*)(receipt == sum ? "Yes" : "No");
}