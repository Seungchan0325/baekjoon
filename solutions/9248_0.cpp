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

vector<int> getLCPArray(const string& s, const vector<int>& sa)
{
    int n = s.size();
    vector<int> lcp(n);

    vector<int> isa(n);
    for(int i = 0; i < n; i++)
        isa[sa[i]] = i;

    int k = 0;
    for(int i = 0; i < n; i++) {
        int idx = isa[i];
        if(idx == n-1) continue;

        int j = sa[idx+1];
        while(max(i, j) + k < n && s[i+k] == s[j+k]) k++;

        lcp[idx] = k;
        if(k > 0) k--;
    }
    return lcp;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    string s;
    cin >> s;
    auto sa = getSuffixArray(s);
    auto lcp = getLCPArray(s, sa);

    int n = s.size();
    for(int i = 0; i < n; i++)
        cout << sa[i] + 1 << " ";
    cout << "\nx ";
    for(int i = 0; i < n - 1; i++)
        cout << lcp[i] << " ";
}