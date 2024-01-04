#include <bits/stdc++.h>

using namespace std;

int n;
vector<long long> h;

int main() {
    cin>>n;
    for(int i=0; i<n; i++) {
        long long a; cin>>a;
        h.push_back(a);
    }

    int ans = 0;
    for(int i=0; i<n; i++) {
        int sum = 0;
        for(int j=0; j<n; j++) {
            if(i == j) continue;

            bool flag = false;
            long long leg = abs(i - j);
            long long height = max(h[i], h[j]) - min(h[i], h[j]);

            for(int k=min(i, j) + 1; k<=max(i, j) - 1; k++) {
                long long legA;
                if((h[j] < h[i] && j < i) || (h[i] < h[j] && i < j)) {
                    legA = k - min(i, j);
                } else {
                    legA = max(i, j) - k;
                }

                if((h[k] - min(h[i], h[j])) * leg >= legA * height) {
                    flag = true;
                }
            }

            if(!flag) {
                sum++;
            }
        }

        ans = max(sum, ans);
    }

    cout<<ans;
}