#include <bits/stdc++.h>

using namespace std;

const int NINF = -987654321;

int d, p;

long long f(int start, int depth, long long v)
{
    if(v >= pow(10LL, d)) return -1;
    if(depth == p) return v;

    long long ret = NINF;
    for(int i = start; i <= 9; i++)
    {
        ret = max(f(i, depth + 1, v * i), ret);
    }

    return ret;
}

int main()
{
    cin >> d >> p;
    long long result = f(2, 0, 1);
    cout << result;
}