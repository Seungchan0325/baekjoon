#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

using line = pair<int, int>;

inline bool InRange(line line1, line line2) { 
    return ((line1.first <= line2.first) && (line2.first <= line1.second)
            && (line1.first <= line2.second) && (line2.second <= line1.second));
}

vector<line> MergeWoods(vector<line>& woods) {
    vector<line> ans;
    ans.push_back(woods.front());
    for(auto& i : woods) {
        if(i.first <= ans.back().second && ans.back().first <= i.second) {
            ans.back().first = min(ans.back().first, i.first);
            ans.back().second = max(ans.back().second, i.second);
        } else {
            ans.push_back(i);
        }
    }
    return ans;
}

int main() {
    int n, q, non;
    cin >> n >> q;
    vector<line> woods(n);
    for(auto& i : woods) { cin >> i.first >> i.second >> non; }
    vector<line> q_lr(q);
    for(auto& i : q_lr) cin >> i.first >> i.second;

    vector<line> merged_ans(q);
    for(int i = 0; i < q; i++) {
        merged_ans[i].first = min(woods[q_lr[i].first-1].first, 
            woods[q_lr[i].second-1].first);
        merged_ans[i].second = max(woods[q_lr[i].first-1].second, 
            woods[q_lr[i].second-1].second);
    }
    
    auto sorted_woods = woods;
    sort(sorted_woods.begin(), sorted_woods.end());
    auto merged_woods = MergeWoods(sorted_woods);

    for(auto& i : merged_ans) {
        for(auto& j : merged_woods) {
            if(InRange(j, i)) {
                cout << "1\n";
                goto CONTINUE;
            }
        }
        cout << "0\n";
        CONTINUE:{}
    }
}