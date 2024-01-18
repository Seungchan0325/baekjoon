#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string str1, str2;
    cin >> str1 >> str2;

    int str1_len = str1.length();
    int str2_len = str2.length();

    vector<vector<int>> table(str1_len+1, vector<int>(str2_len+1));

    for (int i = 1; i <= str1_len; i++) {
        for (int j = 1; j <= str2_len; j++) {
            if (str1[i-1] == str2[j-1]) {
                table[i][j] = table[i - 1][j - 1] + 1;
            } else {
                table[i][j] = max(table[i - 1][j], table[i][j - 1]);
            }
        }
    }
    cout << table.back().back() << endl;
    
    if(table.back().back() != 0) {
        string result;
        int x=str1.size(), y=str2.size();
        while(x != 0 && y != 0) {
            if(str1[x-1] == str2[y-1]) {
                result.push_back(str1[x-1]);
                x--; y--;
            }
            else if(table[x][y] == table[x-1][y]){
                x--;
            }
            else{
                y--;
            }
        }
        reverse(result.begin(), result.end());
        cout<<result<<endl;
    }
}