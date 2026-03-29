#include <bits/stdc++.h>
#include <vector>

using namespace std;

int main()
{
    int M, N;
    cin >> M >> N;
    vector<int> v;
    for(int i = 0; i < N; i++) {
        v.push_back(M/N + M%N);
        M -= M/N + M%N;
    }
    sort(v.begin(), v.end(), greater<>());
    for(auto i : v) cout << i << " ";
    cout << "\n";
    cout << M << "\n";
}
