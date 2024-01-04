#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(void) {
    int number = 1;
    for(int i = 0; i < 3; i++) {
        int temp;
        cin >> temp;
        number *= temp;
    }

    string num = to_string(number);
    
    vector<int> num_count(10);
    for(const auto& i : num) {
        num_count[i - 48]++;
    }
    for(const auto& i : num_count) {
        cout << i << endl;
    }
}