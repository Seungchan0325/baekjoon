#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(void) {
    int test_case;
    cin >> test_case;

    cin.ignore();
    for(int i = 0; i < test_case; i++) {
        string input;
        getline(cin, input);
        
        int score = 0;
        int count = 1;
        for(int i = 0; i < input.size() - 1; i++) {
            if(input[i] == 'O'){
                score += count;
            }else if(input[i] == 'X'){
                count = 1;
            }
            
            if(input[i] == 'O' && input[i + 1] == input[i]){
                count++;
            }else{
                count = 1;
            }
        }
        if(input.back() == 'O'){
            score += count;
        }
        cout << score << endl;
    }
}
// 5
// OOXXOXXOOO
// OOXXOOXXOO
// OXOXOXOXOXOXOX
// OOOOOOOOOO
// OOOOXOOOOXOOOOX