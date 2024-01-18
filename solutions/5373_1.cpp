#include <bits/stdc++.h>

using namespace std;

enum PlaneType {U,D,F,B,L,R};

using pii = pair<int, int>;
using tiii = tuple<int, int, int>;

const array<pair<int, int>, 8> table = {
    pair<int, int>{0, 0},
    pair<int, int>{0, 1},
    pair<int, int>{0, 2},
    pair<int, int>{1, 2},
    pair<int, int>{2, 2},
    pair<int, int>{2, 1},
    pair<int, int>{2, 0},
    pair<int, int>{1, 0},
};

const array<tiii, 12> sides[6] = {
    {tiii{B, 0, 2}, tiii{B, 0, 1}, tiii{B, 0, 0}, tiii{R, 0, 2}, tiii{R, 0, 1}, tiii{R, 0, 0}, tiii{F, 0, 2}, tiii{F, 0, 1}, tiii{F, 0, 0}, tiii{L, 0, 2}, tiii{L, 0, 1}, tiii{L, 0, 0}},
    {tiii{B, 2, 0}, tiii{B, 2, 1}, tiii{B, 2, 2}, tiii{L, 2, 0}, tiii{L, 2, 1}, tiii{L, 2, 2}, tiii{F, 2, 0}, tiii{F, 2, 1}, tiii{F, 2, 2}, tiii{R, 2, 0}, tiii{R, 2, 1}, tiii{R, 2, 2}},
    {tiii{U, 2, 0}, tiii{U, 2, 1}, tiii{U, 2, 2}, tiii{R, 0, 0}, tiii{R, 1, 0}, tiii{R, 2, 0}, tiii{D, 2, 0}, tiii{D, 2, 1}, tiii{D, 2, 2}, tiii{L, 2, 2}, tiii{L, 1, 2}, tiii{L, 0, 2}},
    {tiii{U, 0, 2}, tiii{U, 0, 1}, tiii{U, 0, 0}, tiii{L, 0, 0}, tiii{L, 1, 0}, tiii{L, 2, 0}, tiii{D, 0, 2}, tiii{D, 0, 1}, tiii{D, 0, 0}, tiii{R, 2, 2}, tiii{R, 1, 2}, tiii{R, 0, 2}},
    {tiii{U, 0, 0}, tiii{U, 1, 0}, tiii{U, 2, 0}, tiii{F, 0, 0}, tiii{F, 1, 0}, tiii{F, 2, 0}, tiii{D, 2, 2}, tiii{D, 1, 2}, tiii{D, 0, 2}, tiii{B, 2, 2}, tiii{B, 1, 2}, tiii{B, 0, 2}},
    {tiii{U, 2, 2}, tiii{U, 1, 2}, tiii{U, 0, 2}, tiii{B, 0, 0}, tiii{B, 1, 0}, tiii{B, 2, 0}, tiii{D, 0, 0}, tiii{D, 1, 0}, tiii{D, 2, 0}, tiii{F, 2, 2}, tiii{F, 1, 2}, tiii{F, 0, 2}},
};

char colors[] = "wyrogb";
char cube[6][3][3];

PlaneType AsciiToPlane[256];

void rotate_ccw(PlaneType plane) {
    queue<char> q;
    for(auto [x, y] : table) {
        q.push(cube[plane][x][y]);
    }
    q.push(q.front()); q.pop();
    q.push(q.front()); q.pop();
    for(auto [x, y] : table) {
        cube[plane][x][y] = q.front(); q.pop();
    }
    
    queue<char> qq;
    for(auto [other_plane, x, y] : sides[plane]) {
        qq.push(cube[other_plane][x][y]);
    }
    qq.push(qq.front()); qq.pop();
    qq.push(qq.front()); qq.pop();
    qq.push(qq.front()); qq.pop();
    for(auto [other_plane, x, y] : sides[plane]) {
        cube[other_plane][x][y] = qq.front(); qq.pop();
    }
}

void print() {
    for(int i = 0; i < 6; i++) {
        for(int x = 0; x < 3; x++) {
            for(int y = 0; y < 3; y++) {
                cout << cube[i][x][y];
            }
            cout << "\n";
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    AsciiToPlane['U'] = U;
    AsciiToPlane['D'] = D;
    AsciiToPlane['F'] = F;
    AsciiToPlane['B'] = B;
    AsciiToPlane['L'] = L;
    AsciiToPlane['R'] = R;
    int tc; cin >> tc;
    while(tc--) {
        for(int i = 0; i < 6; i++) {
            memset(cube[i], colors[i], 3*3);
        }
        int n; cin >> n;
        for(int i = 0; i < n; i++) {
            string op; cin >> op;
            int cnt = (op[1] == '-') ? 1 : 3;
            while(cnt--) {
                rotate_ccw(AsciiToPlane[op[0]]);
            }

            // cout << "---------------------------\n";
            // print();
        }

        for(int x = 0; x < 3; x++) {
            for(int y = 0; y < 3; y++) {
                cout << cube[U][x][y];
            }
            cout << "\n";
        }
    }
}