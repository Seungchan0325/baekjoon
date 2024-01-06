#include <bits/stdc++.h>

using namespace std;

int main()
{
    int a, b, c;
    cin >> a >> b;
    cin >> c;

    int t = 60 * a + b + c;
    cout << (t / 60) % 24 << " " << t % 60;
}