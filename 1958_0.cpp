#include <iostream>
#include <algorithm> //max(...)
#include <string>

using namespace std;

string str[3];
int dp[101][101][101];

int lcs() {
    for(int i=1; i<=str[0].size(); i++)
        for(int j=1; j<=str[1].size(); j++)
            for(int k=1; k<=str[2].size(); k++) {
                if(str[0][i-1] == str[1][j-1] && str[1][j-1] == str[2][k-1])
                    dp[i][j][k] = dp[i-1][j-1][k-1] + 1;
                else
                    dp[i][j][k] = max({dp[i-1][j][k], dp[i][j-1][k], dp[i][j][k-1]});
            }

    int ret = dp[str[0].size()][str[1].size()][str[2].size()];
    return ret;
}

int main() {
    for(auto&i:str)
        cin>>i;
    
    int result = lcs();

    cout<<result<<endl;
}