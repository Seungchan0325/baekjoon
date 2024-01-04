#include <iostream>
#include <algorithm>
#include <array>
#include <vector>

using namespace std;

struct COORD {
    int x, y;
};

const vector<vector<int>> rect_board = {
    {0, 0, 0, 1, 1, 1, 2, 2, 2},
    {0, 0, 0, 1, 1, 1, 2, 2, 2},
    {0, 0, 0, 1, 1, 1, 2, 2, 2},
    {3, 3, 3, 4, 4, 4, 5, 5, 5},
    {3, 3, 3, 4, 4, 4, 5, 5, 5},
    {3, 3, 3, 4, 4, 4, 5, 5, 5},
    {6, 6, 6, 7, 7, 7, 8, 8, 8},
    {6, 6, 6, 7, 7, 7, 8, 8, 8},
    {6, 6, 6, 7, 7, 7, 8, 8, 8}
};
const vector<COORD> rect_start_points = {
    {0, 0}, {3, 0}, {6, 0},
    {0, 3}, {3, 3}, {6, 3},
    {0, 6}, {3, 6}, {6, 6},
};
vector<vector<int>> board(9, vector<int>(9));

bool check_rect(COORD pos, int n) {
    COORD rect = rect_start_points[rect_board[pos.y][pos.x]];
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(board[i+rect.y][j+rect.x] == n)
                return false;

    return true;
}

bool check_xy(COORD pos, int n) {
    for(int i=0; i<9; i++)
        if(board[pos.y][i] == n || board[i][pos.x] == n)
            return false;
    return true;
}

inline bool check(COORD pos, int n) {
    return check_rect(pos, n) && check_xy(pos, n);
}

void func(COORD pos) {
    if(pos.x == 0 && pos.y == 9) {
        for(auto& i : board) {
            for(auto& j : i){
                printf("%d", j);
            }
            printf("\n");
        }
        exit(0);
        return;
    }
    
    if(board[pos.y][pos.x] != 0){
        if(pos.x == 8)
            func({0, pos.y+1});
        else
            func({pos.x+1, pos.y});
        return;
    }

    for(int k = 1; k <= 9; k++) {
        if(!check(pos, k)) continue;

        board[pos.y][pos.x] = k;
        if(pos.x == 8)
            func({0, pos.y+1});
        else
            func({pos.x+1, pos.y});
        board[pos.y][pos.x] = 0;
    }
}

int main() {
    for(auto& i : board) {
        for(auto& j : i){
            scanf("%1d", &j);
        }
    }
    func({0, 0});
}