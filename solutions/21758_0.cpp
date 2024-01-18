#include <iostream>
#include <vector>

using namespace std;

int N;
vector<int> arr1, arr2;

int acc(int start, int end) {
    return arr2[end] - arr2[start];
}

int main() {
    cin >> N;
    arr1.resize(N + 1);
    arr2.resize(N + 1);
    for(int i = 1; i <= N; i++)
        cin >> arr1[i];

    arr2[1] = arr1[1];
    for(int i = 1; i <= N; i++)
        arr2[i] = arr1[i] + arr2[i-1];

    int ans = 0;

    for(int i = 1; i < N-1; i++) {
        //통 벌 벌
        ans = max(acc(0, N-1) - arr1[i+1] + acc(0, i), ans);
        //벌 벌 통
        ans = max(acc(1, N) - arr1[i+1] + acc(i+1, N), ans);
        //벌 통 벌
        ans = max(acc(1, i+1) + acc(i, N-1), ans);
    }
    
    cout << ans << endl;
}