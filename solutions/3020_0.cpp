#include <iostream>
#include <limits>
#include <algorithm>
#include <vector>

using namespace std;

int N, H;
vector<int> input1, input2;

int countI(int i) {
    auto a = lower_bound(input1.begin(), input1.end(), i) - input1.begin();
    return a;
}

int main() {
    cin >> N >> H;
    input1.resize(N/2);
    input2.resize(N/2);
    for(int i = 0; i < N/2; i++)
        scanf("%d %d", &input1[i], &input2[i]);
    sort(input1.begin(), input1.end());
    sort(input2.begin(), input2.end());

    int cnt = 1;
    int ans = numeric_limits<int>::max();
    for(int i = 1; i <= H; i++) {
        int tmp = input1.size() - (lower_bound(input1.begin(), input1.end(), i) - input1.begin());
        tmp += input2.size() - (lower_bound(input2.begin(), input2.end(), H-i+1) - input2.begin());
        if(ans == tmp) cnt++;
        else if(ans > tmp) {
            cnt = 1;
            ans = tmp;
        }
    }
    cout << ans << " " << cnt << endl;
}