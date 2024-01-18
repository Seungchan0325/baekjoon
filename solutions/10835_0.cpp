#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n;
vector<int> lDeck, rDeck;
vector<vector<int>> memoization;

int dfs(int lIdx, int rIdx) {
    if (lIdx == lDeck.size() || rIdx == rDeck.size())
        return 0;

    if (memoization[lIdx][rIdx] != -1)
        return memoization[lIdx][rIdx];

    int ret = -1;
    ret = max(ret, dfs(lIdx+1, rIdx));
    ret = max(ret, dfs(lIdx+1, rIdx+1));
    if(lDeck[lIdx] > rDeck[rIdx])
        ret = max(ret, dfs(lIdx, rIdx+1) + rDeck[rIdx]);

    memoization[lIdx][rIdx] = ret;
    return ret;
}

int main() {
    cin >> n;
    lDeck.resize(n);
    rDeck.resize(n);
    memoization.resize(n, vector<int>(n, -1));
    for (auto& i : lDeck)
        cin >> i;
    for (auto& i : rDeck)
        cin >> i;

    cout << dfs(0, 0) << endl;
}