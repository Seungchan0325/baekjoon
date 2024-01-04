#include <bits/stdc++.h>

using namespace std;

const int MAXN = 55;

int n;
vector<int> arr;

int main() {
    cin >> n;
    arr.resize(n);
    for(int i = 0; i < n; i++) cin >> arr[i];
    sort(arr.begin(), arr.end());

    for(int i = 1; i < n; i++) {
        if(arr[i-1] + 1 == arr[i]) {
            if(arr.back() == arr[i]) {
                int st = arr[i-1];
                int l = i;
                int sz = n - i;
                while(true) {
                    if(arr[l-1] != st || l-1 < 0) break;
                    for(int i = 0; i < sz; i++) {
                        swap(arr[l+i-1], arr[l+i]);
                    }
                    l--;
                }
                break;
            }
            else {
                int l = upper_bound(arr.begin() + i, arr.end(), arr[i]) - arr.begin();
                while(i < l) {
                    swap(arr[l], arr[l-1]);
                    l--;
                }
                i++;
            }
        }
    }

    for(int i = 0; i < n; i++) cout << arr[i] << ' ';
}