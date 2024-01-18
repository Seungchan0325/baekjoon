#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MOD = 1000000007;

class SquareMatrix {
public:
    ll n;
    vector<vector<ll>> matrix;

    SquareMatrix(ll _n) : n(_n), matrix(n, vector<ll>(n, 0)) {}

    vector<ll>& operator [] (ll i) {
        return matrix[i];
    }

    SquareMatrix operator * (SquareMatrix& other) const {
        SquareMatrix ret(n);
        for(ll i = 0; i < n; i++)
            for(ll j = 0; j < n; j++) {
                ll sum = 0;
                for(ll k = 0; k < n; k++) {
                    sum += matrix[i][k] * other[k][j];
                    sum %= MOD;
                }
                ret[i][j] = sum;
            }
        return ret;
    }
};

SquareMatrix Identity(ll n) {
    auto ret = SquareMatrix(n);
    for(ll i = 0; i < n; i++)
        ret[i][i] = 1;
    return ret;
}

SquareMatrix pow(SquareMatrix& matrix, ll m) {
    if(m == 0) return Identity(matrix.n);
    if(m & 1) return pow(matrix, m-1) * matrix;
    SquareMatrix half = pow(matrix, m / 2);
    return half * half;
}

int main() {
    ll n; cin >> n;

    auto base = SquareMatrix(2);
    base[0][1] = base[1][0] = base[1][1] = 1;
    ll fibo = pow(base, abs(n)+1)[0][0];

    cout << fibo;
}