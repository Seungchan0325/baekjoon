#include <bits/stdc++.h>

using namespace std;

struct Comparator {
    const vector<int>& group;
    int t;
    Comparator(const vector<int>& _group, int _t) : group(_group), t(_t) {}
    bool operator () (int a, int b) {
        if(group[a] != group[b]) return group[a] < group[b];
        return group[a + t] < group[b + t];
    }
};

vector<int> getSuffixArray(const string& s) {
    int n = s.size();

    int t = 1;
    vector<int> group(n+1);
    for(int i = 0; i < n; i++) group[i] = s[i];
    group[n] = -1;

    vector<int> perm(n);
    for(int i = 0; i < n; i++) perm[i] = i;
    while(t < n) {
        Comparator compareUsing2T(group, t);
        sort(perm.begin(), perm.end(), compareUsing2T);

        t *= 2;
        if(t >= n) break;

        vector<int> newGroup(n+1);
        newGroup[n] = -1;
        newGroup[perm[0]] = 0;
        for(int i = 1; i < n; i++) {
            if(compareUsing2T(perm[i-1], perm[i]))
                newGroup[perm[i]] = newGroup[perm[i-1]] + 1;
            else
                newGroup[perm[i]] = newGroup[perm[i-1]];
        }
        group = newGroup;
    }
    return perm;
}

int main()
{
    string s;
    cin >> s;

    int n = s.size();
    vector<int> sa = getSuffixArray(s);

    string a = s;
    sort(a.begin(), a.end());
    if(a[0] != 'a') goto EXIST;

    for(int i = 1; i < n; i++) {
        if(a[i] - a[i-1] > 1) goto EXIST;
    }

    for(int i = 1; i < n; i++) {
        if(s[sa[i]] == s[sa[i-1]]) continue;
        char tmp = s[sa[i]];
        s[sa[i]] = s[sa[i-1]];
        if(sa == getSuffixArray(s)) goto EXIST;
        s[sa[i]] = tmp;
    }

NOT_EXIST:
    cout << "0";
    return 0;
EXIST:
    cout << "1";
    return 0;
}