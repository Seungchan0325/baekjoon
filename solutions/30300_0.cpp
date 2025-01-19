#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int T;
    cin >> T;
    while(T--) {
        int N;
        cin >> N;
        vector<int> a;
        a.reserve(N);
        for(int i = 0; i < N; i++) {
            int ai;
            cin >> ai;
            a.push_back(ai);
        }
        vector<int> chk(N+1);

        int ans = 0;
        int mx = -1;
        for(int i = 0; i <= 30; i++) {
            for(int j = 0; j < N; j++) {
                int v = a[j] & ((1<<i)-1);
                if(v < N) chk[v]++;
            }
            int first = -1;
            for(int j = 0; j <= N; j++) {
                if(chk[j] == 0) {
                    first = j;
                    break;
                }
            }
            assert(first != -1);
            if(first > mx) {
                mx = first;
                ans = ((1<<i)-1);
            }
            for(int j = 0; j < N; j++) {
                int v = a[j] & ((1<<i)-1);
                if(v < N) chk[v] = 0;
            }
        }
        cout << ans << "\n";
    }
}