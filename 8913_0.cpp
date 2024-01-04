#include <iostream>
#include <string>

using namespace std;

string s;

int pop_range(const string& str, int start) {
    while(str[start] == str[start+1]) start++;
    return start+1;
}

bool make_empty(string str) {
    if(str.size() <= 1) return str.empty();

    int start = 0, end = 0;
    while((end = pop_range(str, start)) <= str.size()) {
        if(end - start >= 2)
            if(make_empty(str.substr(0, start) + str.substr(end)))
                return true;
        start = end;
    }

    return false;
}

int main() {
    int c;
    cin>>c;
    while(c--) {
        cin>>s;

        bool result = make_empty(s);

        cout<<(result ? 1 : 0)<<endl;
    }
}