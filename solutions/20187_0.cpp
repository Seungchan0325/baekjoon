#include <bits/stdc++.h>

using namespace std;

void vertical_flip(vector<vector<int>>& v)
{
    for(int j = 0; j < v.size(); j++) {
        for(int k = 0; k < v[0].size(); k++) {
            if(v[j][k]&1) v[j][k] = v[j][k] - 1;
            else v[j][k] = v[j][k] + 1;
        }
        int l = 0;
        int r = ssize(v[j])-1;
        while(l < r) {
            swap(v[j][l], v[j][r]);
            l++;r--;
        }
    }
}

void horizon_flip(vector<vector<int>>& v)
{
    for(int j = 0; j < v[0].size(); j++) {
        for(int k = 0; k < v.size(); k++) {
            if(v[k][j] <= 1) v[k][j] = v[k][j]+2;
            else v[k][j] = v[k][j]-2;
        }
        int l = 0;
        int r = ssize(v)-1;
        while(l < r) {
            swap(v[l][j], v[r][j]);
            l++; r--;
        }
    }
}

int main()
{
    int k; cin >> k;
    vector<char> op;
    for(int i = 0; i < 2*k; i++) {
        char c; cin >> c;
        op.push_back(c);
    }
    int h; cin >> h;

    vector<vector<int>> hole(1, vector<int>(1));
    hole[0][0] = h;
    for(int i = 2*k-1; i >= 0; i--) {
        if(op[i] == 'D') {
            auto down = hole;
            auto up = hole;
            horizon_flip(up);
            hole = up;
            hole.insert(hole.end(), down.begin(), down.end());
        } else if(op[i] == 'U') {
            auto up = hole;
            auto down = hole;
            horizon_flip(down);
            hole = up;
            hole.insert(hole.end(), down.begin(), down.end());
        } else if(op[i] == 'R') {
            auto left = hole;
            auto right = hole;
            vertical_flip(left);
            hole = left;
            for(int j = 0; j < hole.size(); j++) {
                hole[j].insert(hole[j].end(), right[j].begin(), right[j].end());
            }
        } else if(op[i] == 'L') {
            auto left = hole;
            auto right = hole;
            vertical_flip(right);
            hole = left;
            for(int j = 0; j < hole.size(); j++) {
                hole[j].insert(hole[j].end(), right[j].begin(), right[j].end());
            }
        }
    }

    for(auto i : hole) {
        for(auto j : i) {
            cout << j << " ";
        }
        cout << "\n";
    }
}