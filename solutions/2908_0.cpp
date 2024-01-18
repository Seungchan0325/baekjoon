#include <iostream>
#include <string>

using namespace std;

string flipOver(const string& str){
    string result;
    int i = str.size();

    while(i--){
        result.push_back(str[i]);
    }
    return result;
}

int main(){
    string num1, num2;
    cin >> num1 >> num2;
    num1 = flipOver(num1); num2 = flipOver(num2);

    cout << (stoi(num1) > stoi(num2) ? num1 : num2) << endl;
}