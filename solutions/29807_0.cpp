#include <bits/stdc++.h>

using namespace std;

int T, score[10], result;

int main()
{
    cin >> T;
    for(int i = 0; i < T; i++) {
        cin >> score[i];
    }

    if(score[0] > score[2]) {
        result += (score[0] - score[2]) * 508;
    } else {
        result += (score[2] - score[0]) * 108;
    }

    if(score[1] > score[3]) {
        result += (score[1] - score[3]) * 212;
    } else {
        result += (score[3] - score[1]) * 305;
    }

    if(T == 5) {
        result += score[4] * 707;
    }

    result *= 4763;
    cout << result;
}