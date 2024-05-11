#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int N, B, A[MAXN], psum[MAXN];

int main()
{
    cin >> N >> B;
    for(int i = 1; i <= N; i++) {
        cin >> A[i];
    }

    vector<int> v;
    int i;
    for(i = 1; i <= N; i++) {
        if(A[i] == B) {
            v.push_back(0);
            break;
        }

        if(A[i] < B) v.push_back(-1);
        else v.push_back(1);
    }
    i++;

    for(int j = v.size() - 2; j >= 0; j--) {
        v[j] += v[j+1];
    }
    sort(v.begin(), v.end());

    int sum = 0;
    int ans = upper_bound(v.begin(), v.end(), 0) - lower_bound(v.begin(), v.end(), 0);
    for(; i <= N; i++) {
        if(A[i] < B) sum--;
        else sum++;

        ans += upper_bound(v.begin(), v.end(), -sum) - lower_bound(v.begin(), v.end(), -sum);
    }

    cout << ans;
}