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

    for(int i = last+1; i < C; i++) {
        if(result.back() > input[i]) continue;
        dfs(result + input[i], i);
    }
}

int main() {
    cin >> L >> C;
    input.resize(C);
    for(auto & i : input) cin >> i;

    sort(input.begin(), input.end());

    for(int i = 0; i < C; i++)
        dfs(string(1, input[i]), i);
}