// #include "grader.cpp"

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010101;

vector<int> compute_pre(char s[], int n)
{
	vector<int> nxt(n);
	int appear[26];
	for(int i = 0; i < 26; i++) appear[i] = -1e9;
	for(int i = 0; i < n; i++) {
		nxt[i] = i - appear[s[i]-'a'];
		appear[s[i]-'a'] = i;
	}
	return nxt;
}

#define chk(i, m) (H[i] == N[matched] || (H[i] > matched && N[matched] > matched))

vector<int> getPi(vector<int>& s)
{
	int n = s.size();
	vector<int> pi(n, 0);
	int matched = 0;
	for(int i = 1; i < n; i++) {
		while(matched > 0 && !((s[i] >= matched && s[matched] >= matched) || s[i] == s[matched]))
			matched = pi[matched - 1];
		if((s[i] >= matched && s[matched] >= matched) || s[i] == s[matched])
			pi[i] = ++matched;
	}
	return pi;
}

int kmp(vector<int>& H, vector<int>& N)
{
	int ans = 0;
	int n = H.size();
 	int m = N.size();
	auto pi = getPi(N);

	int matched = 0;
	for(int i = 0; i < n; i++) {
		while(matched > 0 && !chk(i, matched))
			matched = pi[matched - 1];
		if(chk(i, m)) {
			matched++;
			if(matched == m) {
				ans++;
				matched = pi[matched - 1];
			}
		}
	}
	return ans;
}

int findP(char T[], char P[], int N, int M)
{
	auto pre_t = compute_pre(T, N);
	auto pre_p = compute_pre(P, M);
	int ans = kmp(pre_t, pre_p);
	return ans;
}
