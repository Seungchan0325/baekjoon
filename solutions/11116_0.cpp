#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while(t--) {
        int m;
        cin >> m;
        int c = 0;
        vector<int> a(m), b(m);
        for(auto&i:a) cin >> i;
        for(auto&i:b) cin >> i;
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        for(auto i : a) {
            if(binary_search(a.begin(), a.end(), i+500) && binary_search(b.begin(), b.end(), i+1000) && binary_search(b.begin(), b.end(), i+1500)) {
                c++;
            }
        }
        cout << c << "\n";
    }
}