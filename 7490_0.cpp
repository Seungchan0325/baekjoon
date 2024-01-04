#include <bits/stdc++.h>

using namespace std;

int n;

int calc(string str) {
    int ret = 0;
    int digit = 0;
    int num = 0;
    reverse(str.begin(), str.end());
    for(int i = 0; i < str.size(); i++) {
        if('0' <= str[i] && str[i] <= '9') {
            num += (str[i] - '0') * pow(10, digit);
            digit++;
        }

        switch(str[i]) {
            case '+':
                ret += num;
                //cout << num << "\n";
                num = 0;
                digit = 0;
            break;
            case '-':
                ret -= num;
                //cout << num << "\n";
                num = 0;
                digit = 0;
            break;
            case ' ':
            break;
        }
    }
    ret += num;

    return ret;
}

void f(int times, string num_st) {
    if(times == n) {
        int number = calc(num_st);
        if(number == 0) cout << num_st << "\n";
        return;
    }

    f(times + 1, num_st+" "+to_string(times+1));
    f(times + 1, num_st+"+"+to_string(times+1));
    f(times + 1, num_st+"-"+to_string(times+1));
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int tc;
    cin >> tc;
    while(tc--) {
        cin >> n;
        f(1, "1");
        cout << "\n";
    }
}