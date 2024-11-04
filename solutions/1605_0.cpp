#include <bits/stdc++.h>

using namespace std;

struct Comparator {
    const vector<int>& group;
    int t;
    Comparator(const vector<int>& group, int t) : group(group), t(t) {}

    bool operator()(int a, int b) {
        if(group[a] != group[b]) return group[a] < group[b];
        return group[a+t] < group[b+t];
    }
};

vector<int> getSA(const string& s)
{
    int n = s.size();

    int t = 1;
    vector<int> group(n+1);
    for(int i = 0; i < n; i++) group[i] = s[i];
    group[n] = -1;

    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    while(t < n) {
        Comparator compareUsing2T(group, t);
        sort(perm.begin(), perm.end(), compareUsing2T);

        t *= 2;
        if(t >= n) break;

        vector<int> newGroup(n+1);
        newGroup[n] = -1;
        newGroup[perm[0]] = 0;
        for(int i = 1; i < n; i++) {
            if(compareUsing2T(perm[i-1], perm[i])) {
                newGroup[perm[i]] = newGroup[perm[i-1]] + 1;
            } else {
                newGroup[perm[i]] = newGroup[perm[i-1]];
            }
        }
        group = newGroup;
    }

    return perm;
}

vector<int> getLCP(const string& s, const vector<int>& sa)
{
    int n = s.size();
    vector<int> pos(n);
    for(int i = 0; i < n; i++) pos[sa[i]] = i;

    vector<int> lcp(n, 0);
    for(int i = 0, k = 0; i < n; i++, k = max(k-1, 0)) {
        if(pos[i] == n-1) continue;
        for(int j = sa[pos[i]+1]; s[i+k] == s[j+k]; k++);
        lcp[pos[i]] = k;
    }

    return lcp;
}

int main()
{
    int L;
    string s;
    cin >> L;
    cin >> s;

    auto sa = getSA(s);
    auto lcp = getLCP(s, sa);

    cout << *max_element(lcp.begin(), lcp.end());
}