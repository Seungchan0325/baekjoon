#include <iostream>
#include <vector>
#include <string>

using namespace std; using namespace std::string_literals;

void draw_star(vector<string>& map, int x, int y, int size){
    if(size <= 1){
        map[y][x] = '*';
        return;
    }

    for(int i = 0; i < 3; i++) {
        int _x = x;
        for(int j = 0; j < 3; j++) {
            if(i == 1 && j == 1){
                _x += size/3;
                continue;
            }
            draw_star(map, _x, y, size/3);
            _x += size/3;
        }
        y += size/3;
    }
}

int main(){
    int n;
    cin >> n;

    vector<string> map(n);
    for(auto & i : map)
        i.resize(n, ' ');

    draw_star(map, 0, 0, n);

    for(const auto & str : map){
        cout << str << endl;
    }
}