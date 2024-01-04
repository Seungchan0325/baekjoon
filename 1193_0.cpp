#include <iostream>
#include <utility>

using namespace std;

pair<int, int> zigzag(int x){
    int a = 0, Olda, b; // a:각지그재그번째마다의 끝 번호   b:지그재그 번째
    for(int i = 1; a < x; i++){
        b = i;
        Olda = a;
        a += i;
    }
    return pair<int, int>(Olda+1, b);
}

int main(){
    int x;
    cin >> x;
    
    pair<int, int> result = zigzag(x);

    int a = x - result.first;
    if(result.second%2 == 0)
        cout << a+1 << '/' << result.second - a << endl;
    else
        cout << result.second - a << '/' << a+1 << endl;
}