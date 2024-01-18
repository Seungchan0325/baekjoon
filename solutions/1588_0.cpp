#include <bits/stdc++.h>

using namespace std;

class SquareMatrix {
public:
    int n;
    vector<vector<int>> matrix;

    SquareMatrix(int _n) : n(_n), matrix(n, vector<int>(n, 0)) {}

    vector<int>& operator [] (int i) {
        return matrix[i];
    }

    SquareMatrix operator + (const SquareMatrix& other) const {
        SquareMatrix ret(n);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                ret[i][j] = matrix[i][j] + other.matrix[i][j];
            }
        }
        return ret;
    }

    SquareMatrix operator - (const SquareMatrix& other) const {
        SquareMatrix ret(n);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                ret[i][j] = matrix[i][j] - other.matrix[i][j];
            }
        }
        return ret;
    }

    SquareMatrix operator * (const SquareMatrix& other) const {
        SquareMatrix ret(n);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++) {
                int sum = 0;
                for(int k = 0; k < n; k++) {
                    sum += matrix[i][k] * other.matrix[k][j];
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

SquareMatrix pow(const SquareMatrix& matrix, int m) {
    if(m == 0) return Identity(matrix.n);
    if(m & 1) return pow(matrix, m-1) * matrix;
    SquareMatrix half = pow(matrix, m / 2);
    return half * half;
}

const int _next[3][3] = {
    {0, 2, 1},
    {1, 0, 0},
    {1, 2, 1}
};

SquareMatrix f(int n, int idx, int start)
{
    if(idx < 0) {
        return SquareMatrix(3);
    }
    if(n == 0) {
        SquareMatrix ret(3);
        ret[0][start] = 1;
        return ret;
    }
    int i = 0;
    long long sum = 0;
    while((sum + pow(3, n - 1)) <= idx) {
        sum += pow(3, n - 1);
        i++;
    }

    SquareMatrix mat(3);
    for(int j = 0; j < i; j++) {
        mat[0][_next[start][j]]++;
    }

    SquareMatrix base(3);
    base[0][0] = base[0][1] = base[0][2] = base[1][1] = base[2][2] = 1;
    base[1][0] = base[2][1] = 2;

    return mat * pow(base, n - 1) + f(n - 1, idx - sum, _next[start][i]);
}

int main()
{
    int start, N, Left, Right;
    cin >> start;
    cin >> Left;
    cin >> Right;
    cin >> N;

    SquareMatrix result = f(N, Right, start - 1) - f(N, Left - 1, start - 1);
    for(int i = 0; i < 3; i++) cout << result[0][i] << " ";
}