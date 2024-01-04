#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

long long int N, cnt = 0;
vector<int> A, B, C, D, 
            AB, CD;

int main() {
    cin >> N;
    A.resize(N); B.resize(N); C.resize(N); D.resize(N);

    for(int i = 0; i < N; i++)
            cin >> A[i] >> B[i] >> C[i] >> D[i];

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            AB.push_back(A[i] + B[j]);
            CD.push_back(C[i] + D[j]);
        }
    }

    sort(AB.begin(), AB.end());
    sort(CD.begin(), CD.end());

    for(int i = 0; i < N*N; i++) {
        cnt += upper_bound(AB.begin(), AB.end(), -CD[i]) - lower_bound(AB.begin(), AB.end(), -CD[i]);
    }

    cout << cnt << "\n";
}