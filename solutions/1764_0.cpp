#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    map<string, int> mp;
    for(int i = 0; i < n; i++) {
        string input;
        cin >> input;
        mp[input]++;
    }
    for(int i = 0; i < m; i++) {
        string input;
        cin >> input;
        mp[input]++;
    }
    string ans;
    int cnt = 0;
    for(auto i : mp) {
        if(i.second >= 2) {
            ans.append(i.first);
            ans.append("\n");
            cnt++;
        }
    }
    cout << cnt << endl;
    cout << ans;
}