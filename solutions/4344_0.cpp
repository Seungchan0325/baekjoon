#include <iostream>
#include <string>
#include <math.h>
#include <vector>

using namespace std;

int main(void) {
    int test_case = 0;
    cin >> test_case;

    for(int i = 0; i < test_case; i++) {
        int n;
        cin >> n;
        
        int average = 0;
        vector<int> input(n);
        for(int j = 0; j < n; j++) {
            cin >> input[j];
            average += input[j];
        }
        average /= n;

        int pass_num = 0;
        for(int j = 0; j < n; j++) {
            if(average < input[j]) pass_num++;
        }
        float result = (float)pass_num / (float)n * 100;
        printf("%.3lf%\n", result);
    }
}