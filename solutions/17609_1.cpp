#include <iostream>
#include <string.h>

using namespace std;

int T;
char str[100001];

bool _is_palindrome(int left, int right) {
    while(left < right) {
        if(str[left] != str[right]) return false;
        left++; right--;
    }
    return true;
}

int is_palindrome(int left, int right) {
    while(left < right) {
        if(str[left] == str[right]) {
            left++; right--;
            continue;
        }
        
        if(_is_palindrome(left+1, right) || _is_palindrome(left, right-1))
            return 1;
        else
            return 2;
    }
    return 0;
}

int main() {
    scanf("%d", &T);
    while(T--) {
        //memset(str, 0, sizeof(str));
        scanf("%s", str);
        printf("%d\n", is_palindrome(0, strlen(str)-1));
    }
}