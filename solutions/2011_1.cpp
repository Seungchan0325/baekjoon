#include <iostream>
#include <string>

using namespace std;

const int MOD = 1000000;
string inp;
int dp[5005] = {1};

int main() {
    cin>>inp;
    inp = "0" + inp;

    for(int i=1; i<inp.size(); i++) {
        if(inp[i] != '0')
            dp[i] = dp[i-1];
        if(10 <= stoi(inp.substr(i-1, 2)) && stoi(inp.substr(i-1, 2)) <= 26) {
            dp[i] += dp[i-2];
            dp[i] %= MOD;
        }
    }

    cout<<dp[inp.size()-1];
}