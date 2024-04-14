#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int T;
    cin >> T;
    for(int t = 1; t <= T; t++) {
        int N, K;
        cin >> N >> K;

        vector<int> v;
        v.push_back({-1});
        for(int i = 0; i < N; i++) {
            int x; cin >> x;
            if(x > v.back()) {
                v.push_back(x);
            } else {
                *lower_bound(v.begin(), v.end(), x) = x;
            }
        }
        cout << "Case #" << t << "\n";
        cout << (int)(K <= v.size() - 1) << "\n";
    }
}