#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n;
    cin >> n;
    while(n--) {
        string s;
        cin >> s;
        int i = 0;
        while(true) {
            bool flag = true;
            int k = i;
            for(int j = s.size() - 1; j >= 0; j--) {
                if(k >= s.size()) break;
                if(s[k] != s[j]) {
                    flag = false;
                    break;
                }
                k++;
            }
            if(flag) break;
            i++;
        }
        for(int j = 0; j < i; j++) cout << s[j];
        for(int j = s.size()-1; j >= 0; j--) cout << s[j];
        cout << "\n";
    }
}