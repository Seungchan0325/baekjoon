#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n;
vector<int> lDeck, rDeck;

int dfs(int lIdx, int rIdx) {
    if (lIdx == lDeck.size() || rIdx == rDeck.size())
        return 0;

    int ret = -1;
    ret = max(ret, dfs(lIdx+1, rIdx));
    ret = max(ret, dfs(lIdx+1, rIdx+1));
    if(lDeck[lIdx] > rDeck[rIdx])
        ret = max(ret, dfs(lIdx, rIdx+1) + rDeck[rIdx]);

    return ret;
}

int main() {
    cin >> n;
    lDeck.resize(n);
    rDeck.resize(n);
    for (auto& i : lDeck)
        cin >> i;
    for (auto& i : rDeck)
        cin >> i;

    cout << dfs(0, 0) << endl;
}