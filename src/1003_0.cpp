#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

int dp[41][2] = {{1,0},{0,1}};

int fibonacci(int n) {
    dp[n][0] = dp[n-1][0]+dp[n-2][0];
    dp[n][1] = dp[n-1][1]+dp[n-2][1];
	    
    return 0;
}

int main() {
	int t,n;
	
	cin >> t;
	
	for(int i=2;i<41;i++)
       fibonacci(i);
    
    for(int i=0;i<t;i++){
       cin >> n;
       cout << dp[n][0] << " " << dp[n][1] << endl;
    }

	return 0;
}