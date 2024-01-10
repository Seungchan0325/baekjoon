#include <bits/stdc++.h>

using namespace std;

tuple<long long, long long, long long> countXYZ(int n, long long X, long long Y, long long Z)
{
    for(int i = 1; i < n; i++) {
        long long tmpX, tmpY, tmpZ;
        tmpX = X;
        tmpY = Y;
        tmpZ = Z;
        X = tmpZ;
        Y = tmpX;
        Z = tmpX + tmpY;
    }
    return make_tuple(X, Y, Z);
}

char gen(int n, long long idx, char c)
{
    if(n == 1) return c;

    if(c == 'X') {
        auto [X, Y, Z] = countXYZ(n - 1, 0, 1, 0);
        if(idx < X + Y + Z) return gen(n - 1, idx, 'Y');
        else return gen(n - 1, idx - X - Y - Z, 'Z');
    } else {
        return gen(n - 1, idx, c == 'Y' ? 'Z' : 'X');
    }
}

int main()
{
    int type, n;
    cin >> type >> n;

    if(type == 1) {
        auto [X, Y, Z] = countXYZ(n, 1, 0, 0);
        cout << X + Y + Z;
    } else if(type == 2) {
        long long k;
        cin >> k;
        cout << gen(n, k - 1, 'X');
    } else {
        char c;
        cin >> c;
        auto [X, Y, Z] = countXYZ(n, 1, 0, 0);
        if(c == 'X') cout << X;
        else if(c == 'Y') cout << Y;
        else cout << Z;
    }
}