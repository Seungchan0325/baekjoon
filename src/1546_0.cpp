#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(void) {
    int SubjectCount = 0;
    cin >> SubjectCount;
    float *inputs = new float[SubjectCount];
    for (int i = 0; i < SubjectCount; i++) {
        cin >> inputs[i];
    }

    int max = 0;
    for (int i = 0; i < SubjectCount; i++) {
        if(inputs[i]>max) max = inputs[i];
    }
    
    float average;
    for(int i = 0; i < SubjectCount; i++) {
        //printf("%lf\n", inputs[i]);
        average += inputs[i] / max * 100;
    }
    // average /= SubjectCount;
    cout << (float)average / (float)SubjectCount << endl;
}