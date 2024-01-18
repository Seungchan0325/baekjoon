#include <iostream>
#include <limits>
#include <vector>
#include <cassert>

using namespace std;

using my_type = long long;

my_type GetLargestRectArea(const vector<my_type> &heights, my_type l, my_type r) {
    if(l == r) return heights[r];

    my_type mid = (l + r) / 2;

    my_type ret = numeric_limits<int>::min();

    ret = max(GetLargestRectArea(heights, l, mid), 
            GetLargestRectArea(heights, mid + 1, r));

    my_type lo = mid, hi = mid + 1;
    my_type height = min(heights[lo], heights[hi]);

    ret = max(ret, height * 2);

    while(l < lo || hi < r) {
        if(hi < r && (lo == l || heights[lo - 1] < heights[hi + 1])) {
            ++hi;
            height = min(height, heights[hi]);
        } else {
            --lo;
            height = min(height, heights[lo]);
        }

        ret = max(ret, height * (hi - lo + 1));
    }

    return ret;
}

bool solve() {
    my_type n;
    cin >> n;
    if(n == 0) return false;
    vector<my_type> heights(n);
    for(auto& i : heights) cin >> i;
    cout << GetLargestRectArea(heights, 0, n-1) << "\n";
    return true;
}

int main() {
    while(solve());
}