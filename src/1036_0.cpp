#include <bits/stdc++.h>

using namespace std;

const int MAXN = 55;

string table = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int to_int(char c) {
    if(c <= '9') return c - '0';
    else return c - 'A' + 10;
}

void carry(vector<int>& dst) {
    dst.push_back(0);
    for(int i = 0; i+1 < dst.size(); i++) {
        dst[i+1] += dst[i] / 36;
        dst[i] %= 36;
    }
    while(1 < dst.size() && dst.back() == 0) dst.pop_back();
}

void add(vector<int>& dst, const vector<int>& src) {
    int digit1 = 0;
    int digit2 = 0;

    while(digit2 < src.size()) {
        if(digit1 == dst.size()) dst.push_back(0);
        dst[digit1] += src[digit2];
        digit1++; digit2++;
    }

    carry(dst);
}

bool compare(const vector<int>& a, const vector<int>& b) {
    if(a.size() != b.size()) return a.size() < b.size();

    for(int idx = a.size() - 1; idx >= 0; idx--) {
        if(a[idx] != b[idx]) return a[idx] < b[idx];
    }

    // a == b
    return false;
}

int n, k;
vector<int> diff[36];
vector<int> nums[MAXN];

struct cmp {
    bool operator()(const pair<vector<int>, int>& a, const pair<vector<int>, int>& b) const {
        return compare(a.first, b.first);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for(int i = 0; i < n; i++) {
        string input;
        cin >> input;

        reverse(input.begin(), input.end());
        nums[i].reserve(input.size());

        for(int j = 0; j < input.size(); j++)
            nums[i].push_back(to_int(input[j]));
    }
    cin >> k;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < nums[i].size(); j++) {
            int num = nums[i][j];
            vector<int> tmp(j+1);
            tmp[j] = 35 - num;
            add(diff[num], tmp);
        }
    }

    priority_queue<pair<vector<int>, int>, vector<pair<vector<int>, int>>, cmp> pq;
    for(int i = 0; i < 36; i++)
        pq.push(make_pair(diff[i], i));
    
    for(int i = 0; i < k; i++) {
        int num = pq.top().second; pq.pop();
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < nums[j].size(); k++)
                if(nums[j][k] == num) nums[j][k] = 35;
            while(1 < nums[j].size() && nums[j].back() == 0) nums[j].pop_back();
        }
    }

    vector<int> ans;
    for(int i = 0; i < n; i++)
        add(ans, nums[i]);
    for(auto iter = ans.rbegin(); iter != ans.rend(); iter++)
        cout << table[*iter];
}