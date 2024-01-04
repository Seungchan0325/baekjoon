#include <iostream>
#include <algorithm>
#include <string>
#include <stack>

using namespace std;

int main() {
    string str, bomb;
    string st = "";
    cin >> str >> bomb;

    for(std::size_t i = 0; i < str.size(); i++) {
        st.push_back(str[i]);
        if(st.size() >= bomb.size()) {
            if(st.substr(st.size() - bomb.size()) == bomb) {
                st.replace(st.size() - bomb.size(), bomb.size(), "");
            }
        }
    }

    if(st.size() == 0) cout << "FRULA";
    else cout << st;
}