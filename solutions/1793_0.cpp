#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int n;
string dp[260];

int ctoi(const char& a) {
    return a-'0';
}

char itoc(const int& a) {
    return (a%10)+'0';
}

string add(string a, string b) {
        int carry = 0;
    int size = max(a.size(), b.size());
    string ret;

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    a.resize(size, '0');
    b.resize(size, '0');

    for(int i=0; i<size; i++) {
        int sum = ctoi(a[i]) + ctoi(b[i]) + carry;
        carry = sum / 10;
        ret.push_back(itoc(sum));
    }

    if(carry == 1) ret.push_back('1');

    reverse(ret.begin(), ret.end());
    return ret;
}

int main() {
    dp[0] = "1";
    dp[1] = "1";
    dp[2] = "3";

    for(int i=3; i<=250; i++) {
        dp[i] = add(add(dp[i-2], dp[i-2]), dp[i-1]);
    }

    while(cin>>n) {
        cout<<dp[n]<<endl;
    }
}