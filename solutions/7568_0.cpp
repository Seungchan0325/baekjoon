#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct deongchi{
    int hight;
    int weight;
    int lank;
    deongchi() : lank(1){}
};

bool compare(deongchi a, deongchi b){
    return (a.weight < b.weight) && (a.hight < b.hight);
}

int main(){
    int n;
    cin >> n;
    vector<deongchi> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i].weight >> v[i].hight;
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(compare(v[i], v[j])){
                v[i].lank++;
            }
        }
    }

    for(const auto& item : v){
        cout << item.lank << ' ';
    }
}