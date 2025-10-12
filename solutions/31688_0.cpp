#include <bits/stdc++.h>

using namespace std;

const int MAXN = 64;

int N, A[MAXN][MAXN];

int main()
{
    int t; cin >> t;
    while(t--) {
        cin >> N;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                cin >> A[i][j];
            }
        }
        vector<int> v;
        for(int i = 0; i < N; i++) {
            if(i&1) {
                for(int j = 0; j < N; j++) {
                    v.push_back(A[i][j]);
                }
            } else {
                for(int j = N-1; j >= 0; j--) {
                    v.push_back(A[i][j]);
                }
            }
        }

        int diff = 0;
        for(int i = 1; i < v.size(); i++) {
            if(v[i-1] < v[i]) diff--;
            else diff++;
        }
        if(diff < 0) reverse(v.begin(), v.end());
        for(auto i : v) cout << i << " ";
        cout << "\n";
    }
}