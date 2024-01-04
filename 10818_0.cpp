#include <iostream>

using namespace std;

int main(void) {
    int min = 1000000, max = -1000000, n;

    cin >> n;

    for (int i = 0; i < n; i++){
        int temp;
        cin >> temp;

        if (temp < min) min = temp;
        if(max < temp) max = temp;
    }
    cout << min << " " << max;
}