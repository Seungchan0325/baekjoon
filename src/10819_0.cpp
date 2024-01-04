#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;
using llint = long long int;

llint n, _max=LONG_LONG_MIN;
vector<llint> vec;

llint get_value(const vector<llint>& v){
    llint result=0;
    for(llint i=1; i<v.size(); i++)
        result += abs(v[i-1]-v[i]);
    return result;
}

int main() {
    cin >> n;
    vec.resize(n);
    for(auto& i : vec)
        cin >> i;
    
    sort(vec.begin(), vec.end());
    do{
        _max = max(_max, get_value(vec));
	}while(next_permutation(vec.begin(), vec.end()));

    cout << _max;
}