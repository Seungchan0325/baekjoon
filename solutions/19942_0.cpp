#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct nut {
    int p, f, s, v, cost;
    nut operator+(nut a) {
        nut tmp;
        tmp.p = p + a.p;
        tmp.f = f + a.f;
        tmp.s = s + a.s;
        tmp.v = v + a.v;
        tmp.cost = cost + a.cost;
        return tmp;
    }
};

int n, min_cost = numeric_limits<int>::max();
nut min_nut;
vector<int> added;
vector<nut> costes;

void f(int idx, nut total, vector<int> cur) {
    if(idx == n) {
        if((total.p >= min_nut.p) && (total.f >= min_nut.f) &&
           (total.s >= min_nut.s) && (total.v >= min_nut.v) && (total.cost < min_cost)) {
            min_cost = total.cost;
            added = cur;
        }
        return;
    }

    bool is_zero = false;
    if(costes[idx].f == 0 &&
       costes[idx].p == 0 &&
       costes[idx].s == 0 &&
       costes[idx].v == 0)
        is_zero = true;

    if(is_zero == false) {
        cur.push_back(idx+1);
        f(idx+1, total+costes[idx], cur);
        cur.pop_back();
    }
    f(idx+1, total, cur);
}

int main() {
    cin >> n;
    cin >> min_nut.p >> min_nut.f >> min_nut.s >> min_nut.v;

    costes.resize(n);
    for(auto& i : costes)
        cin >> i.p >> i.f >> i.s >> i.v >> i.cost;

    f(0, nut{0, 0, 0, 0, 0}, vector<int>());
    if(min_cost == numeric_limits<int>::max()){
        cout << -1;
    } else {
        cout << min_cost << "\n";
        for(auto& i : added) 
            cout << i << " ";
    }
}