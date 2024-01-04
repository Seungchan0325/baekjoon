#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;

int cache[2505];
string str;

bool is_palindrome(int start, int end) {
    while(start <= end) {
        if(str[start] != str[end]) return false;
        start++; end--;
    }
    return true;
}

int palindrome_division(int start) {
    if(start == str.length()) return 0;

    int& ret = cache[start];
    if(ret != -1) return ret;
    
    ret = INF;
    for(int end = start; end < str.length(); end++)
        if(is_palindrome(start, end))
            ret = min(palindrome_division(end + 1) + 1, ret);
    
    return ret;
}

int main() {
    cin>>str;

    memset(cache, -1, sizeof(cache));
    int result = palindrome_division(0);
    cout<<result;
}