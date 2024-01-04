#include <iostream>
#include <string>

using namespace std;

int main(){
    string input;
    cin >> input;

    int score = 0;
    int bar_cnt = 0;
    for(int i = 0; i < input.size()-1; i++){
        if(input[i]=='('){
            if(input[i+1] == ')'){
                score += bar_cnt;
            }else if(input[i+1] != ')'){
                bar_cnt++;
                score++;
            }
        }
        else if(input[i] == ')' && input[i-1] != '(')
            bar_cnt--;
    }
    cout << score << endl;
}