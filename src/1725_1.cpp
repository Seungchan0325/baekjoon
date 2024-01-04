#include <iostream>

using namespace std;

int N, heights[100000];

int GetLargestRect(int left, int right) {
    if(left == right) return heights[left];

    int ret;
    int mid = (left + right) / 2;
    ret = max(GetLargestRect(left, mid), GetLargestRect(mid+1, right));

    int lo, hi, height;
    lo = mid;
    hi = mid + 1;
    height = min(heights[lo], heights[hi]);

    ret = max(height*2, ret);

    while(left < lo || hi < right) {
        if(hi < right && (lo == left || heights[lo - 1] < heights[hi + 1])) {
            hi++;
            height = min(height, heights[hi]);
        } else {
            lo--;
            height = min(height, heights[lo]);
        }

        ret = max((hi-lo+1)*height, ret);
    }

    return ret;
}

int main() {
    cin>>N;
    for(int i=0; i<N; i++)
        cin>>heights[i];
    
    int result = GetLargestRect(0, N-1);

    cout<<result;
}