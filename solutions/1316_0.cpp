#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
    int n;
    cin >> n;

    int cnt = 0;
    for(int i = 0; i < n; i++){
        bool check[26] = {false};
        string str;
        cin >> str;
        
        bool is_group_word = true;
        for(int j = 0; j < str.size(); j++){
            char c = str[j];
            if(check[c - 'a']) {is_group_word = false; break;}
            if(c != str[j+1]) {check[c - 'a'] = true;}
        }
        cnt += is_group_word;
    }
    cout << cnt << endl;
}