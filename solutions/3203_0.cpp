#include <bits/stdc++.h>

using namespace std;

const int MOD = 10000;

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
                    sum += matrix[i][k] * other[k][j];
                    sum = (sum + MOD) % MOD;
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

void trim(string& s) {
    while(s.front() == ' ' && !s.empty()) s.erase(s.begin());
    while(s.back() == ' ' && !s.empty()) s.pop_back();
}

bool starts_with(const string& s, const string& prefix) {
    return s.rfind(prefix) == 0;
}

SquareMatrix to_mat(const string& s) {
    auto ret = Identity(27);
    stringstream ss(s);
    char dst; ss >> dst;
    dst = dst - 'a' + 1;
    ss.ignore(); // ignore '='
}

struct Block {
    int repeat;
};

vector<string> text;

int main() {
    int block = 1;
    string s; cin >> s; text.push_back(s);
    while(0 < block) {
        getline(cin, s);
        trim(s);
        text.push_back(s);
        if(starts_with(s, "REPEAT")) block++;
        else if(starts_with(s, "STOP")) block--;
    }
}