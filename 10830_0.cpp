#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD = 1000;

class SquareMatrix {
public:
    int n;
    vector<vector<int>> matrix;

    SquareMatrix(int _n) : n(_n), matrix(n, vector<int>(n, 0)) {}

    vector<int>& operator [] (int i) {
        return matrix[i];
    }

    SquareMatrix operator * (SquareMatrix& other) const {
        SquareMatrix ret(n);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++) {
                int sum = 0;
                for(int k = 0; k < n; k++) {
                    sum += matrix[i][k] * other[k][j];
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

SquareMatrix pow(SquareMatrix& matrix, ll m) {
    if(m == 0) return Identity(matrix.n);
    if(m & 1) return pow(matrix, m-1) * matrix;
    SquareMatrix half = pow(matrix, m / 2);
    return half * half;
}

int main() {
    int n; ll b;
    cin >> n >> b;
    auto matrix = SquareMatrix(n);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> matrix[i][j];
    
    auto result = pow(matrix, b);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            cout << result[i][j] << " ";
        cout << "\n";
    }
}