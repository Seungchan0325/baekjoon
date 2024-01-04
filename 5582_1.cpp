#include <iostream>
#include <memory.h> //memset
#include <string>

using namespace std;

string str[2];
int cache[4001][4001];

//longest same sequence
int lss(int index_1, int index_2) {
    if(index_1 >= str[0].size() || index_2 >= str[1].size()) return 0;

    int& ret=cache[index_1][index_2];
    if(ret != -1) return ret;

    if(str[0][index_1] == str[1][index_2])
        ret = lss(index_1+1, index_2+1) + 1;
    else
        ret = 0;

    return ret;
}

int cps() {
    int ret=-1;
    for(int i=0; i<str[0].size(); i++)
        for(int j=0; j<str[1].size(); j++) {
            int _lss = lss(i, j);
            ret = max(ret, _lss);
        }

    return ret;
}

int main() {
    memset(cache, -1, sizeof(cache));

    cin>>str[0]>>str[1];

    int result=cps();
    cout<<result<<"\n";
}