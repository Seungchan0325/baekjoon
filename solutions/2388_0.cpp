#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int N, M;
vector<int> R, C;

int main()
{
    cin >> N >> M;
    R.resize(N); C.resize(M);
    for(int i = 0; i < N; i++) {
        cin >> R[i];
    }
    for(int i = 0; i < M; i++) {
        cin >> C[i];
    }

    sort(R.begin(), R.end());
    sort(C.begin(), C.end());

    if(R.back() != C.back()) {
        cout << -1;
        return 0;
    }

    int min_v = 0;
    int max_v = 0;
    for(int i = 0; i < N; i++) {
        max_v += R[i] * (C.end() - upper_bound(C.begin(), C.end(), R[i]));
    }

    for(int i = 0; i < M; i++) {
        max_v += C[i] * (R.end() - lower_bound(R.begin(), R.end(), C[i]));
    }

    int i, j;
    i = j = 0;
    while(i < N && j < M) {
        if(i < N && j < M && R[i] == C[j]) {
            min_v += R[i] * max(upper_bound(C.begin(), C.end(), C[j]) - lower_bound(C.begin(), C.end(), C[j]),
                         upper_bound(R.begin(), R.end(), R[i]) - lower_bound(R.begin(), R.end(), R[i]));
            i = upper_bound(R.begin(), R.end(), R[i]) - R.begin();
            j = upper_bound(C.begin(), C.end(), C[j]) - C.begin();
        } else if(j == M || (i < N && R[i] < C[j])) {
            min_v += R[i] * (upper_bound(R.begin(), R.end(), R[i]) - lower_bound(R.begin(), R.end(), R[i]));
            i = upper_bound(R.begin(), R.end(), R[i]) - R.begin();
        } else {
            min_v += C[j] * (upper_bound(C.begin(), C.end(), C[j]) - lower_bound(C.begin(), C.end(), C[j]));
            j = upper_bound(C.begin(), C.end(), C[j]) - C.begin();
        }
    }

    cout << min_v << " " << max_v;
}