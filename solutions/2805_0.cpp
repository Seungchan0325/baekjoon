#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

long long int N, M, ans;
vector<long long int> input;

long long int operate(long long int n) {
    long long int sum = 0;
    for(auto& i : input)
        sum += i > n ? i - n : 0;
    return sum;
}

void search() {
    long long int start = 0, end = *max_element(input.begin(), input.end()), mid;
    while(start <= end) {
        mid = (start + end) / 2;
        long long int a = operate(mid);
        if(a >= M) {
            start = mid + 1;
            ans = mid;
        }
        if(a < M) {
            end = mid - 1;
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);
    input.resize(N);
    for(auto& i : input)
        scanf("%d", &i);

    search();
    printf("%d", ans);
}