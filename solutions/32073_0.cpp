#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int tc; cin >> tc;
    while(tc--) {
        int N;
        cin >> N;
        string tmp;
        cin >> tmp;

        string s;
        bool f = false;
        bool f0 = false;
        for(int i = 0; i < N; i++) {
            if(tmp[i] == '1' || f) {
                s.push_back(tmp[i]);
                f = true;
            }

            if(tmp[i] == '0') {
                f0 = true;
            }
        }

        N = s.size();
        if(N == 0) {
            cout << "0\n";
            continue;
        }

        int a = 0;
        for(int i = 0; i < N; i++) {
            if(s[i] == '0') break;
            a++;
        }

        int b = 0;
        for(int i = a; i < N; i++) {
            if(s[i] == '1') break;
            b++;
        }

        string ss = s;

        if(b == 0) {
            if(!f0) ss.back() = '0';
            cout << ss << "\n";
            continue;
        }

        int lst = 0;
        if(a < b) lst = 0;
        else {
            lst = a - b;
        }
        for(int i = a; i < N; i++) {
            if(ss[i] != s[lst]) ss[i] = '1';
            else ss[i] = '0';
            lst++;
        }

        cout << ss << "\n";
    }
}