#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int countBlank(string& str){
    int cnt_blank = 0;
    for(const auto&item : str){
        if(isspace(static_cast<int>(item))){
            cnt_blank++;
        }
    }
    return cnt_blank;
}

int main(){
    string str;
    getline(cin, str);

    int number_of_word = countBlank(str)+1;

    if(isspace(static_cast<int>(str.front())))
        number_of_word--;
    if(isspace(static_cast<int>(str.back())))
        number_of_word--;

    cout << number_of_word << endl;
}