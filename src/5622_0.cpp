#include <iostream>
#include <string>

using namespace std;

int to_integer(char ch){
    int result;
    switch(ch){
        case 'A':case 'B':case 'C':
            result = 1;
            break;
        case 'D':case 'E':case 'F':
            result = 2;
            break;
        case 'G':case 'H':case 'I':
            result = 3;
            break;
        case 'J':case 'K':case 'L':
            result = 4;
            break;
        case 'M':case 'N':case 'O':
            result = 5;
            break;
        case 'P':case 'Q':case 'R':case 'S':
            result = 6;
            break;
        case 'T':case 'U':case 'V': 
            result = 7;
            break;
        case 'W':case 'X':case 'Y':case 'Z':
            result = 8;
            break;
    }
    return result;
}

int get_time(int num){
    return num + 2;
}

int main(){
    string num;
    cin >> num;

    int min_time = 0;
    for(const auto& ch : num){
        min_time += get_time(to_integer(ch));
    }
    cout << min_time << endl;
}