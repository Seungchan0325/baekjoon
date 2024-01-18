#include <bits/stdc++.h>

using namespace std;

int main() {
    int n; cin >> n;

    int sum = 0;
    int digit = 0;
    int cnt[10] = {0};
    for(int remain = n; remain; remain /= 10) {
        int v = remain % 10;
        // x i {0~y}
        for(int i = 0; i < v; i++) {
            //0 0 {0~y}
            if(i == 0 && remain / 10 == 0) continue;
            cnt[i] += pow(10, digit);
        }
        // x v {0~y}
        cnt[v] += sum + 1;
        // {0~x} i {0~y}
        for(int i = 0; i < 10; i++) {
            if(i == 0) cnt[i] += (max(remain / 10 - 1, 0)) * pow(10, digit);
            else cnt[i] += (remain / 10) * pow(10, digit);
        }
        sum += v * pow(10, digit++);
    }

    for(int i = 0; i < 10; i++) cout << cnt[i] << " ";
    cout << "\n";
}