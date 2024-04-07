#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<pair<int, int>> A, B;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    A.resize(N);
    for(int i = 0; i < N; i++) {
        cin >> A[i].first;
        A[i].second = i;
    }
    cin >> M;
    B.resize(M);
    for(int i = 0; i < M; i++) {
        cin >> B[i].first;
        B[i].second = i;
    }

    sort(A.begin(), A.end(), [](pair<int, int> a, pair<int, int> b) {
        if(a.first != b.first) return a.first > b.first;
        return a.second < b.second;
    });
    sort(B.begin(), B.end(), [](pair<int, int> a, pair<int, int> b) {
        if(a.first != b.first) return a.first > b.first;
        return a.second < b.second;
    });

    vector<int> ans;
    int i, j, lstA, lstB;
    i = j = 0;
    lstA = lstB = -1;
    while(i < N && j < M) {
        if(A[i].first == B[j].first && lstA < A[i].second && lstB < B[j].second) {
            ans.push_back(A[i].first);
            lstA = A[i].second;
            lstB = B[j].second;
            i++; j++;
        } else if(A[i].first > B[j].first || (A[i].first == B[j].first && lstA > A[i].second)) {
            i++;
        } else {
            j++;
        }
    }

    cout << ans.size() << "\n";
    for(auto i : ans) cout << i << " ";
}