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
        int count = 0;
        for(int i = 0; i < input.size(); i++) {
            if(input[i] == 'O')count++;
            else count = 0;
            score+=count;
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