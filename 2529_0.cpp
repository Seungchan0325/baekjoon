#include <iostream>
#include <climits>
#include <string>

using namespace std;

int k;
string input, _min = to_string(LONG_LONG_MAX), _max = to_string(LONG_LONG_MIN);

bool is_can(string& numes, int new_num) {
    if(numes.size() == 0) return true;
    int last = numes.back() - '0';
    switch(input[numes.size()-1]) {
        case '<':
            if(last < new_num)
                return true;
            else
                return false;
        
        case '>':
            if(last > new_num) 
                return true;
            else
                return false;
    }
}

void f(string numes) {
    if(numes.size() == k + 1){
        if(stoll(_max) < stoll(numes))
            _max = numes;
        if(stoll(_min) > stoll(numes))
            _min = numes;
        return;
    }

    for(int i = 0; i < 10; i++) {
        if(numes.find(to_string(i)) == string::npos && is_can(numes, i)) {
            f(numes + to_string(i));
        }
    }
}

int main() {
    cin >> k;

    input.resize(k);
    for(int i=0; i<k; i++) {
        cin >> input[i];
    }
    f(string());

    cout << _max << "\n" << _min << "\n";
}