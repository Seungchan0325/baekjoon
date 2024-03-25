#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long a, b, c;
    cin >> a >> b >> c;
    long long dist = abs(a) + abs(b);
    cout << (const char*)((c - dist) % 2 == 0 && c >= dist ? "YES" : "NO");
}