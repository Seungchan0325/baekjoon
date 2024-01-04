#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(void) {
    vector<int> input(10);
    for (int i = 0; i < 10; i++) {
        cin >> input[i];
        input[i] %= 42;
    }

    sort(input.begin(), input.end());
    int different_values_count = 1;
    for(int i = 0; i < 9; i++) {
        if(input[i] != input[i+1]){
            different_values_count++;
        }
    }
    cout << different_values_count << endl;
}