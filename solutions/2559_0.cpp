#include <iostream>
#include <vector>

using namespace std;

int main() {
    int _max = -1e9;
    int n, k;
    cin >> n >> k;

    vector<int> v(n);
    for(auto& i : v) cin >> i;

    int tmp = 0;
    for(int i = 0; i < k; i++)
        tmp+=v[i];
    
    for(int i = 0; i <= n - k; i++) {
        _max = max(_max, tmp);
        tmp += -v[i] + v[i+k];
    }

    cout << _max << endl;
}