#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;
const int MAXK = 105;

int n, k, arr[MAXK];
int plugs[MAXN];

int main() {
    cin >> n >> k;
    for(int i = 0; i < k; i++) cin >> arr[i];
    
    int ans = 0;
    for(int i = 0; i < k; i++) {
        if(find(plugs, plugs + n, arr[i]) != plugs + n) continue;

        int max_idx = -1;
        int* max_v = 0;
        for(int j = 0; j < n; j++) {
            if(plugs[j] == 0) {
                max_idx = j;
                break;
            }
            auto pos = find(arr + i + 1, arr + k, plugs[j]);
            if(max_v <= pos) {
                max_v = pos;
                max_idx = j;
            }
        }

        if(plugs[max_idx] != 0) {

            ans++;
        }
        plugs[max_idx] = arr[i];
    }

    cout << ans;
}