#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> costes;

int operate(int n) {
    int sum = 0;
    for(auto i : costes) {
        sum += min(i, n);
    }
    return sum;
}

int main() {
    int n, max_cost, answer;
    cin >> n;
    costes.resize(n);
    for(auto& i : costes)
        cin >> i;
    cin >> max_cost;
    
    int start = 0, end = *max_element(costes.begin(), costes.end()), mid;
    while(start <= end) {
        mid = (start + end) / 2;
        int a = operate(mid);
        if(a <= max_cost) {
            start = mid + 1;
            answer = mid;
        }
        else if(a > max_cost)
            end = mid - 1;
    }
    cout << answer;
}