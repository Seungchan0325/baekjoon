#include <iostream>
#include <limits.h>
#include <vector>

using namespace std;

int N;
vector<int> arr;

int main() {
    ios_base :: sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);

    cin >> N;
    arr.resize(N);
    for(auto& i : arr) 
        cin >> i;
    

    int cur = 0, _max = -1e9;
    for(int i = 0; i < N; i++) {
        if(cur + arr[i] < 0) {
            _max = max(_max, arr[i]);
            cur = 0;
            continue;
        }

        cur += arr[i];
        _max = max(_max, cur);
    }
    cout << _max;
}