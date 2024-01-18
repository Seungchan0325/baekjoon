#include <iostream>
#include <string>

using namespace std;

int main(){
    string str;
    cin >> str;

    int index = 0;
    for(int i = 0; i < 26; i++){
        cout << (int)str.find(i + 'a') << ' ';
    }
}