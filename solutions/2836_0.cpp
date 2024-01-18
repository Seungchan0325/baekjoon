#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

bool in_range(int min, int max, int x) {
    return min <= x && x < max;
}

int N, M;
long long answer;

int main() {
    cin>>N>>M;
    vector<pair<int, int>> reverse_input;
    for(int i=0; i<N; i++) {
        int a, b;
        cin>>a>>b;

        if(b<a) {
            reverse_input.push_back({b, a});
        }
    }
    answer = M;

    sort(reverse_input.begin(), reverse_input.end());

    int l=-1, r=-1;
    for(auto&i:reverse_input) {
        if(r<i.first) {
            answer += (r - l) * 2;
            l = i.first;
        }
        r = max(r, i.second);
    }
    answer += (r - l) * 2;
    cout<<answer<<endl;
}