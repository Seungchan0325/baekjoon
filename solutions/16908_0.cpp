#include <bits/stdc++.h>

using namespace std;


struct Comparator {
    const vector<int>& group;
    int t;
    Comparator(const vector<int>& _group, int _t) : group(_group), t(_t) {}
    bool operator () (int a, int b) {
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
            newGroup[perm[i]] = newGroup[perm[i-1]] + compareUsing2T(perm[i-1], perm[i]);
        }
        group = newGroup;
    }
    return perm;
}

vector<int> getLCP(const string& s, const vector<int> sa)
{
    int n = s.size();
    vector<int> lcp(n), isa(n);
    for(int i = 0; i < n; i++) isa[sa[i]] = i;
    int k = 0;
    for(int i = 0; i < n; i++) {
        if(isa[i] == 0) continue;
        for(int j = sa[isa[i]-1]; s[i+k] == s[j+k]; k++);
        lcp[isa[i]] = k;
        if(k > 0) k--;
    }
    return lcp;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n = 0, l[10] = {0, }, r[10] = {0, }, cnt[10] = {0, }, k = 0;
    string s;
    cin >> n;
    for(int i = 0; i < n; i++) {
        string T;
        cin >> T;
        l[i] = s.size();
        s += T;
        r[i] = s.size();
        s += (char)('{'+i);
    }

    auto sa = getSA(s);
    auto lcp = getLCP(s, sa);

    int ans = 0;
    int j = 0;
    priority_queue<int, vector<int>, greater<>> pq, epq;
    for(int i = 0; i < s.size(); i++) {
        while(k < n && j < s.size()) {
            for(int iter = 0; iter < n; iter++) {
                if(l[iter] <= sa[j] && sa[j] < r[iter]) {
                    if(cnt[iter]++ == 0) k++;
                    break;
                }
            }
            pq.push(lcp[j]);
            j++;
        }
        epq.push(lcp[i]);
        if(k == n) {
            while(pq.size() && epq.size() && pq.top() == epq.top()) {
                pq.pop(); epq.pop();
            }
            ans = max(ans, pq.top());
        }
        for(int iter = 0; iter < n; iter++) {
            if(l[iter] <= sa[i] && sa[i] < r[iter]) {
                if(--cnt[iter] == 0) k--;
                break;
            }
        }
    }
    cout << ans << "\n";
}