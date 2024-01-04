#include <iostream>

using namespace std;

int main(void) {
    int max = -2147483647;
    int max_index = 0;

    for(int i = 0; i < 10; i++) {
        int temp;
        cin >> temp;
        if(temp > max){
            max = temp;
            max_index = i + 1;
        }
    }

    cout << max  << endl << max_index << endl;
}