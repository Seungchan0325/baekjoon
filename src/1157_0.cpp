#include <iostream>
#include <string>
#include <vector>

using namespace std;

int indexOf(char ch){
    return ch - (ch < 'a' ? 'A' : 'a');
}

int main(){
    string str;
    cin >> str;
    vector<int> alpabet_data(26, -1);
    for(const auto& item : str){
        alpabet_data[indexOf(item)]++;
    }

    int max = -2147483647;
    int max_index = 0;
    bool is_multi_max = false;
    for(int i = 0; i < alpabet_data.size(); i++){
        auto item = alpabet_data[i];
        if(item > max){
            max = item;
            max_index = i;
            is_multi_max = false;
            continue;
        }
        if(item == max){
            is_multi_max = true;
        }
    }

    if(is_multi_max){
        cout << '?' << endl;
        return 0;
    }
    cout << static_cast<char>(max_index + 'A') << endl;
}