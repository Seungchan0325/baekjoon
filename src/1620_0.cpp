#include <iostream>
#include <algorithm>
#include <map>
#include <string>

using namespace std;

#define endl "\n"

int N, M;
map<string, int> st_i;
map<int, string> i_st;

bool is_digit(string in) {
    char* p;
    strtol(in.c_str(), &p, 10);
    return *p == 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>N>>M;
    for(int i=0; i<N; i++) {
        string input;
        cin>>input;
        st_i[input] = i+1;
        i_st[i+1]   = input;
    }
    for(int i=0; i<M; i++) {
        string quest;
        cin>>quest;
        if(is_digit(quest)) {
            cout<<i_st[stoi(quest)]<<endl;
        } else {
            cout<<st_i[quest]<<endl;
        }
    }
}