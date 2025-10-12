#include <bits/stdc++.h>

using namespace std;

const int MAXK = 1010;

int N, K, X[MAXK], R[MAXK], C[MAXK], PR[MAXK], PC[MAXK], PV[MAXK];

int main()
{
    cin >> N >> K;
    vector<int> v;
    for(int i = 0; i < K; i++) {
        cin >> X[i] >> R[i] >> C[i]; R[i]--, C[i]--;
        v.push_back(X[i]);
    }

    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    for(int i = 0; i < v.size(); i++) {
        PV[i] = v[i];
        PR[i] = (v[i]-1) / N;
        PC[i] = (v[i]-1) % N;
    }

    for(int i = 0; i < K; i++) {
        int j = lower_bound(v.begin(), v.end(), X[i]) - v.begin();
        int ans = 0;
        if(C[i] >= PC[j]) ans += C[i] - PC[j];
        else ans += N + C[i] - PC[j];
        if(R[i] >= PR[j]) ans += R[i] - PR[j];
        else ans += N + R[i] - PR[j];
        cout << ans << "\n";
        for(int k = 0; k < v.size(); k++) {
            if(PR[j] == PR[k] && v[k] != X[i]) {
                PC[k] = (PC[k] + C[i] - PC[j] + N) % N;
            }
        }
        PC[j] = C[i];
        for(int k = 0; k < v.size(); k++) {
            if(PC[j] == PC[k] && v[k] != X[i]) {
                PR[k] = (PR[k] + R[i] - PR[j] + N) % N;
            }
        }
        PR[j] = R[i];
    }
}