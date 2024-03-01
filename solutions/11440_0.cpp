#include <bits/stdc++.h>

using namespace std;

using llint = long long;

const llint MOD = 1000000007;

struct Matrix
{
    llint mat[2][2];


    Matrix(int _mat[][2])
    {
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                mat[i][j] = _mat[i][j];
            }
        }
    }

    Matrix()
    {
        memset(mat, 0, sizeof(mat));
    }

    llint* operator [] (int idx)
    {
        return mat[idx];
    }

    Matrix operator * (const Matrix& other) const
    {
        Matrix ret;
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                llint sum = 0;
                for(int k = 0; k < 2; k++) {
                    // ret[i][j] += mat[i][k] * mat[k][j];
                    // ret[i][j] %= MOD;
                    sum += (mat[i][k] * other.mat[k][j]) % MOD;
                    sum %= MOD;
                }
                ret[i][j] = sum;
            }
        }
        return ret;
    }
};

Matrix Identity = (int[][2]){{1, 0}, {0, 1}};
Matrix base = (int[][2]){{0, 1}, {1, 1}};

Matrix pow(const Matrix& a, llint n)
{
    if(n == 0) return Identity;
    if(n & 1) return pow(a, n-1) * a;
    auto half = pow(a, n/2);
    return half * half;
}

int main()
{
    llint N;
    cin >> N;

    llint result = pow(base, N+1)[0][0];
    result *= pow(base, N+2)[0][0];
    result %= MOD;
    cout << result;
}