#include <iostream>
#include <vector>

using namespace std;

int N, K;
vector<int> arr, dp(10000);

int main() {
    cin >> N >> K;
    arr.resize(N);
    for(auto& i : arr)
        cin >> i;

    dp[0] = 1;
    for(int i = 0; i < N; i++)
        for(int j = arr[i]; j <= K; j++)
            dp[j] += dp[j - arr[i]];

    cout << dp[K];
}