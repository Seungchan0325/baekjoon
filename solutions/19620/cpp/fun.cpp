#ifdef LSC_ENV
// #include "grader.cpp"
#include "test.cpp"
#endif

#include "fun.h"

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 101010;

int dep[MAXN], own[MAXN];

vector<int> createFunTour(int N, int Q) {
    int cent = 0;
    int sub = N;
    for(int i = 1; i < N; i++) {
        if(int s = attractionsBehind(0, i); s >= (N+1)/2 && s < sub) {
            cent = i;
            sub = s;
        }
    }

    vector<int> S[3];
    vector<int> nearcent;
    for(int i = 0; i < N; i++) {
        if(i == cent) continue;
        dep[i] = hoursRequired(cent, i);
        if(dep[i] == 1) nearcent.push_back(i);
    }
    for(int i = 0; i < N; i++) {
        if(i == cent) continue;
        int closest = -1;
        int dist = 1e9;
        for(int j = 0; j < 2 && j < nearcent.size(); j++) {
            if(int d = hoursRequired(nearcent[j], i); d < dist) {
                closest = j;
                dist = d;
            }
        }
        if(dist < dep[i]) S[closest].push_back(i), own[i] = closest;
        else S[2].push_back(i), own[i] = 2;
    }

    for(int i = 0; i < 3; i++) sort(S[i].begin(), S[i].end(), [&](int i, int j){return dep[i] < dep[j];});
    
    auto next = [&](int ignore)
    {
        int ret = -1;
        for(int i = 0; i < 3; i++) {
            if(ignore == i) continue;
            if(S[i].size()) {
                if(ret == -1) ret = i;
                else if(dep[S[ret].back()] < dep[S[i].back()]) {
                    ret = i;
                } else if(dep[S[ret].back()] == dep[S[i].back()] && S[ret].size() < S[i].size()) {
                    ret = i;
                }
            }
        }
        return ret;
    };

    vector<int> ans;
    int now = -1;
    while(max({S[0].size(), S[1].size(), S[2].size()}) < (S[0].size()+S[1].size()+S[2].size()+1)/2) {
        now = next(now);
        ans.push_back(S[now].back());
        S[now].pop_back();
    }

    if(S[0].size() < S[1].size()) {
        swap(S[0], S[1]);
        if(now != 2) now = 0^1^now;
    }
    if(S[1].size() < S[2].size()) {
        swap(S[1], S[2]);
        if(now != 0) now = 1^2^now;
    }
    if(S[0].size() < S[1].size()) {
        swap(S[0], S[1]);
        if(now != 2) now = 0^1^now;
    }
    if(S[1].size() && S[2].size()) {
        if(dep[S[1].back()] > dep[S[2].back()]) {
            swap(S[1], S[2]);
            if(now != 0) now = 1^2^now;
        }
        if(now == 1 && dep[S[1].back()] != dep[S[2].back()]) {
            ans.push_back(S[2].back());
            S[2].pop_back();
        }
    }
    S[1].insert(S[1].end(), S[2].begin(), S[2].end());
    if(now == 2) now = 1;
    sort(S[1].begin(), S[1].end(), [&](int i, int j){return dep[i] < dep[j];});

    now = 1^now;
    if(now < 0) now = next(2);
    if(S[0].size() < S[1].size()) S[0].insert(S[0].begin(), cent);
    else if(S[0].size() > S[1].size()) S[1].insert(S[1].begin(), cent);
    else {
        S[now].insert(S[now].begin(), cent);
    }

    assert(abs(ssize(S[0])-ssize(S[1])) <= 1);
    
    int a = ans.size();

    while(S[0].size()+S[1].size()) {
        ans.push_back(S[now].back());
        S[now].pop_back();
        now = 1^now;
    }

    return ans;
}
