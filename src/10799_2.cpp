#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main(){
    string input;
    stack<char> st;
    cin >> input;

    int score = 0;
    int bar_cnt = 0;
    for(int i = 0; i < input.size()-1; i++){
        if(input[i] == '(' && input[i+1] == ')')
            score += bar_cnt;
        else if(input[i] == '(' && input[i+1] != ')'){
            bar_cnt++;
            score++;
        }
        else if(input[i] == ')' && input[i-1] != '(')
            bar_cnt--;
    }
    cout << score << endl;
}