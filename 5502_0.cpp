#include <iostream>
#include <string>

#include <memory.h> //memset

using namespace std;

int n;
int cache[5001][5001];
string str;

int palindrome(int left, int right) {
    if(left >= right) return 0;

    int& ret = cache[left][right];
    if(ret != -1) return ret;

    if(str[left] == str[right]) {
        ret = palindrome(left+1, right-1);
    } else {
        ret = min(
            palindrome(left+1, right) + 1,
            palindrome(left, right-1) + 1
        );
    }

    return ret;
}

int main() {
    memset(cache, -1, sizeof(cache));

    cin>>n>>str;

    int result = palindrome(0, n-1);

    cout<<result<<endl;
}