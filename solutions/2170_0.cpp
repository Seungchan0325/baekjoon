#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;
typedef pair<int, int> P;
const int INF = 1e9+1;
 
int main(){
    int N;
    scanf("%d", &N);
    P L[1000000];
    for(int i=0; i<N; i++){
        int s, e;
        scanf("%d %d", &s, &e);
        L[i] = P(s, e);
    }
    // 선분들을 왼쪽 끝 좌표 순으로 정렬
    sort(L, L+N);
 
    // [l, r]: 현재 합치고 있는 구간
    int result = 0, l = -INF, r = -INF;
    for(int i=0; i<N; i++){
        // 현재 구간과 이번 선분이 합쳐질 수 없음
        if(r < L[i].first){
            // 결과에 더함
            result += r-l;
            // 현재 구간을 이번 선분으로 초기화
            l = L[i].first;
            r = L[i].second;
        }
        // 합쳐짐: 현재 구간의 r을 늘릴 수 있으면 늘림
        else r = max(r, L[i].second);
    }
    result += r-l; // 마지막 구간도 결과에 더해 줌
    printf("%d\n", result);
}