#include <iostream>
#include <algorithm>
#include <string>
#include <stack>

using namespace std;

int main() {
    stack<char> st;
    string input;
    cin >> input;

    int result = 0, mul = 1;
    for(int i = 0; i < input.size(); i++) {
        char cur = input[i];
        switch(cur) {
            case '(':
                st.push(cur);
                if(input[i+1] == ')') {
                    result += 2 * mul;
                } else {
                    mul *= 2;
                }
                break;
            case '[':
                st.push(cur);
                if(input[i+1] == ']') {
                    result += 3 * mul;
                } else {
                    mul *= 3;
                }
                break;
            case ')':
                if(!st.empty()) {
                    if(st.top() == '(')
                        st.pop();
                } else {
                    goto imp;
                }
                if(input[i-1] != '(')
                    mul /= 2;
                break;
            case ']':
                if(!st.empty()) {
                    if(st.top() == '[')
                        st.pop();
                } else {
                    goto imp;
                }
                if(input[i-1] != '[')
                    mul /= 3;
                break;
        }
    }

    if(!st.empty())
        cout << 0 << endl;
    else
        cout << result << endl;
    return 0;
    
imp:
    cout << 0 << endl;
}