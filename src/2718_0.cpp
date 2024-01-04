#include <iostream>
#include <memory.h>

using namespace std;

const int state_cases[6][6] = {
    {5, 2, 2, 1, 1, 1},
    {2, 2, 1, 0, 1, 1},
    {2, 1, 2, 0, 1, 1},
    {1, 0, 0, 1, 0, 0},
    {1, 1, 1, 0, 2, 1},
    {1, 1, 1, 0, 1, 1}
};

int n;
int cache[500][6];

/*
 * 0
 * O O
 * O O
 * O O
 * 
 * 1
 * X O
 * X O
 * O O
 * O O
 * 
 * 2
 * O O
 * O O
 * X O
 * X O
 * 
 * 3
 * X O
 * O O
 * O O
 * X O
 * 
 * 4
 * O O
 * X O
 * X O
 * O O
 * 
 * 5
 * X O
 * X O
 * X O
 * X O
 * 
*/

int tilling(int width, int state) {
    int& ret = cache[width][state];
    if(ret != -1) return ret;

    ret = 0;
    for(int next_state=0; next_state<6; next_state++) {
        if(state_cases[state][next_state] != 0)
            ret += tilling(width-2, next_state) * state_cases[state][next_state];
    }

    return ret;
}

void init() {
    memset(cache, -1, sizeof(cache));
    cache[0][0] = 1; cache[0][1] = 0; cache[0][2] = 0; cache[0][3] = 0; cache[0][4] = 0; cache[0][5] = 0;
    cache[1][0] = 1; cache[1][1] = 1; cache[1][2] = 1; cache[1][3] = 0; cache[1][4] = 1; cache[1][5] = 1;
}

int main() {
    init();
    int tc;
    cin>>tc;
    while(tc--) {
        cin>>n;
        int result = tilling(n, 0);
        cout<<result<<endl;
    }
}