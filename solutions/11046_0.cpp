#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<int> arr;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n;
    arr.push_back(-1);
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        arr.push_back(x);
        arr.push_back(-1);
    }

    int nn = arr.size();
    int p = 0;
    int r = 0;
    vector<int> A(nn);
    for(int i = 0; i < nn; i++) {
        if(i <= r)
            A[i] = min(A[2 * p - i], r - i);
        else
            A[i] = 0;
        
        int left = i - A[i] - 1;
        int right = i + A[i] + 1;
        while(0 <= left && right < nn && arr[left] == arr[right]) {
            A[i]++;
            left--;
            right++;
        }

        if(r < i + A[i]) {
            r = i + A[i];
            p = i;
        }
    }

    cin >> m;
    for(int i = 0; i < m; i++) {
        int s, e;
        cin >> s >> e;
        int mid = (e + s) - 1;
        cout << ((e - s + 1) <= A[mid]) << "\n";
    }
}