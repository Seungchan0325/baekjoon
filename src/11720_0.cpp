#include<iostream>
#include<string>

using namespace std;

int to_number(char ch){
    return (ch - '0');
}

int main(){
    int n;
    int result = 0;
    cin >> n;

    string numberes;
    cin >> numberes;
    for(const auto& ch : numberes){
        result += to_number(ch);
    }
    cout << result << endl;
}