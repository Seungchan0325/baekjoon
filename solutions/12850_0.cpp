#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000007;

class SquareMatrix {
public:
    int n;
    vector<vector<int>> matrix;

    explicit SquareMatrix(int _n) : n(_n), matrix(n, vector<int>(n, 0)) {}

    vector<int>& operator [] (int i) {
        return matrix[i];
    }

    SquareMatrix operator * (SquareMatrix& other) const {
        SquareMatrix ret(n);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++) {
                int sum = 0;
                for(int k = 0; k < n; k++) {
                    sum += ((long long)matrix[i][k] * other[k][j]) % MOD;
                    sum %= MOD;
                }
                ret[i][j] = sum;
            }
        return ret;
    }
};

SquareMatrix Identity(int n) {
    auto ret = SquareMatrix(n);
    for(int i = 0; i < n; i++)
        ret[i][i] = 1;
    return ret;
}

SquareMatrix pow(SquareMatrix& matrix, int m) {
    if(m == 0) return Identity(matrix.n);
    if(m & 1) return pow(matrix, m-1) * matrix;
    SquareMatrix half = pow(matrix, m / 2);
    return half * half;
}

int main() {
    int d; cin >> d;
    SquareMatrix base(8);
    base[0][1] = base[0][2] = 1;
    base[1][0] = base[1][2] = base[1][3] = 1;
    base[2][0] = base[2][1] = base[2][3] = base[2][4] = 1;
    base[3][1] = base[3][2] = base[3][4] = base[3][5] = 1;
    base[4][2] = base[4][3] = base[4][5] = base[4][7] = 1;
    base[5][3] = base[5][4] = base[5][6] = 1;
    base[6][5] = base[6][7] = 1;
    base[7][4] = base[7][6] = 1;

    int result = pow(base, d)[0][0];
    cout << result;
}