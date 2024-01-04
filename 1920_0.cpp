#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
const int MAXM = 100005;

int n, m;
int arr[MAXN], table[MAXM];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for(int i = 0; i < n; i++) cin >> arr[i];
    cin >> m;
    for(int i = 0; i < m; i++) cin >> table[i];

    sort(arr, arr + n);
    for(int i = 0; i < m; i++) {
        cout << binary_search(arr, arr + n, table[i]) << "\n";
    }
}