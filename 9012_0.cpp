#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        string input;
        cin >> input;
        bool stop = false;
        stack<char> remember;
        for(auto& c : input){
            if(c == '(')
                remember.push(c);
            if(c == ')'){
                if(remember.empty()){
                    cout << "NO" << endl;
                    stop = true;
                    break;
                }
                remember.pop();
            }
        }
        if(remember.empty() && !stop){
            cout << "YES" << endl;
        }
        else if(!stop){
            cout << "NO" << endl;
        }
    }
}