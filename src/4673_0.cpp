#include <iostream>
#include <string>

using namespace std;
const int MAX = 10001;

inline int to_number(char ch){
    return (ch - '0');
};

int D(int num){
    string numStr = to_string(num);

    int result = 0;
    for(const auto& i : numStr){
        result += to_number(i);
    }
    result += stoi(numStr);
    return result;
}

int main(void){
    bool not_selfnum[MAX] = {false};

    // << D(36) << endl;
    for(int i=1; i<MAX; i++){
        int d = D(i);
        if(d > MAX) continue;
        not_selfnum[d] = true;
    }

    for(int i=1; i<MAX; i++) {
        if(!not_selfnum[i])
            printf("%d\n", i);
    }
}