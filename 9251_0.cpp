#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string str1, str2;
    cin >> str1 >> str2;

    str1 = "0" + str1;
    str2 = "0" + str2;

    int str1_len = str1.length();
    int str2_len = str2.length();

    vector<vector<int>> table(str1_len, vector<int>(str2_len));

    for (int i = 1; i < str1_len; i++) {
        for (int j = 1; j < str2_len; j++) {
            if (str1[i] == str2[j]) {
                table[i][j] = table[i - 1][j - 1] + 1;
            } else {
                table[i][j] = max(table[i - 1][j], table[i][j - 1]);
            }
        }
    }
    cout << table.back().back() << endl;
}