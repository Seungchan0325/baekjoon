#include <iostream>
#include <string.h>

using namespace std;

int T;
char str[100001];

bool _is_palindrome(int left, int right) {
    while(left < right) {
        if(str[left] == str[right]) {
            left++; right--;
            continue;
        }
        return false;
    }
    return true;
}

int is_palindrome(int left, int right) {
    int ret=0;
    while(left < right) {
        if(str[left] == str[right]) {
            left++; right--;
            continue;
        }
        
        if(_is_palindrome(left+1, right) || _is_palindrome(left, right-1))
            ret=1;
        else
            ret=2;
        break;
    }
    return ret;
}

int main() {
    scanf("%d", &T);
    while(T--) {
        //memset(str, 0, sizeof(str));
        scanf("%s", str);
        printf("%d\n", is_palindrome(0, strlen(str)-1));
    }
}