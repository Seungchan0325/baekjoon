#include <iostream>
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

inline std::ostream& operator<< (std::ostream& ost, const pair<int, string>& item)
{
    printf("%d %s\n", item.first, item.second.c_str());
    return ost;
}

int main(){
    int n;
    cin >> n;
    vector<pair<int, string>> vec(n);
    for(auto& i : vec)
        cin >> i.first >> i.second;
    
    stable_sort(vec.begin(), vec.end(), [](const pair<int, string>& a, const pair<int, string>& b){
        return a.first < b.first;
    });

    for(auto& i : vec)
        cout << i;
}