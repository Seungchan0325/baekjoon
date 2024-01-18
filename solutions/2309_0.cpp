#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    int heights[9];
    for(int i = 0; i < 9; i++) cin >> heights[i];
    sort(heights, heights + 9);

    int start = 0, end = 8, x = accumulate(heights, heights + 9, 0) - 100;
    while(start < end) {
        int a = heights[start] + heights[end];
        if(a == x)
            break;
        else if(a > x)
            end--;
        else if(a < x)
            start++;
    }

    for(int i = 0; i < 9; i++)
        if(!(i == start || i == end))
            cout << heights[i] << endl;
}