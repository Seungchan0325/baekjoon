#include <bits/stdc++.h>

using namespace std;

const int MAXK = 66;

int K, vote[3*MAXK];

int main()
{
    cin >> K;
    for(int i = 1; i <= 3*K; i++) cin >> vote[i];
    vector<int> v(3*K);
    iota(v.begin(), v.end(), 1);
    sort(v.begin(), v.end(), [&](int i, int j){return vote[i]<vote[j];});
    random_device rd;
    mt19937 g(rd());
    for(int iter = 0; iter < 100000; iter++) {
        shuffle(v.begin()+K, v.end(), g);
        int A = 0, B = 0;
        for(int i = 0; i < K; i++) A += vote[v[i+K]];
        for(int i = 0; i < K; i++) B += vote[v[i+2*K]];
        if(A > 500*K && B > 500*K) {
            for(int i = 0; i < 3*K; i++) cout << v[i] << "\n";
            return 0;
        }
    }
}