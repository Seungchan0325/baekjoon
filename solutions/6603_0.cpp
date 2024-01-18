#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int _size;
vector<int> vec;
vector<bool> flags;

void f(int cnt, string s, int prev) {
    if(cnt == 6) {
        cout << s << "\n";
        return;
    }

    for(int i=prev; i<_size; i++) {
        if(flags[i] == true) continue;

        flags[i] = true;
        f(cnt+1, s+to_string(vec[i])+' ', i);
        flags[i] = false;
    }
}

int main() {
    while(true) {
        cin >> _size;
        if(_size == 0) break;
        vec.resize(_size);

        for(auto& i : vec)
            cin >> i;
        flags.resize(_size);
        fill(flags.begin(), flags.end(), false);    
        f(0, string(), 0);
        cout << "\n";
    }
}