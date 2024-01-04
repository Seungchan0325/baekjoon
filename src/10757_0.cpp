#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

int to_num(char c){
    if(c >= '0' && c <= '9')
        return c - '0';
    else return 0;
}
char to_char(int c){return c + '0';}

int main(){
    string a, b;

    cin >> a >> b;
    string result;
    bool pick_up = false;
    while(!a.empty() || !b.empty()){
        int add = to_num(a.back()) + to_num(b.back());
        if(pick_up) add++;
        pick_up = false;
        result.push_back(to_char(add % 10));
        if(!a.empty())a.pop_back(); if(!b.empty()) b.pop_back();
        if(add >= 10) pick_up = true;
    }
    if(pick_up)result.push_back('1');
    reverse(result.begin(), result.end());
    cout << max(a, b) << result << endl;
}