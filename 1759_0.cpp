//dfs
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string vowel = "aeiou";
int L, C;
string input;

void dfs(string result, int last) {
    if(last > C) return;
    if(result.length() == L) {
        int vowel_cnt = 0;

        for(auto i : result)
            for(auto j : vowel)
                if(j == i)
                    vowel_cnt++;
        
        if(vowel_cnt < 1 || L - vowel_cnt < 2) return;
        cout << result << "\n";
        return;
    }
    if(result.back() < input[last+1])
        dfs(result + input[last+1], last+1);
    dfs(result, last+1);
}

int main() {
    cin >> L >> C;
    input.resize(C);
    for(auto & i : input) cin >> i;

    sort(input.begin(), input.end());

    for(int i = 0; i < C; i++)
        dfs(string(1, input[i]), i);
}