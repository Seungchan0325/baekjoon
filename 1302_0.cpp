#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    int n;
    cin >> n;
    map<string, int> m;
    for(int i = 0; i < n; i++) {
        string input;
        cin >> input;
        m[input]++;
    }

    pair<string, int> ans = {"", -1e9};
    for(auto i : m) {
        if(ans.second < i.second) {
            ans = i;
        }
    }
    cout << ans.first;
}