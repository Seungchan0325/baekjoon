#include <bits/stdc++.h>

using namespace std;

int main() {
    while(true) {
        string input;
        cin >> input;
        if(input == "0") break;

        bool flag = true;
        int lo = 0, hi = input.size()-1;
        while(lo < hi) {
            if(input[lo] != input[hi]) {
                flag = false;
                break;
            }
            lo++; hi--;
        }

        if(flag) cout << "yes\n";
        else cout << "no\n";
    }
}