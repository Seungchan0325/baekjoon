#ifdef LSC_ENV
#include "grader.cpp"
#endif

#include "cactus.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXN = 505050;
const int L = 20;
const ll inf = 1e18;

ll n, h[MAXN], s[MAXN], lpos[MAXN][L], lsum[MAXN][L], rpos[MAXN][L], rsum[MAXN][L];

void init(std::vector<int> H) {
	n = H.size();
	h[0] = h[n+1] = inf;
	for(int i = 0; i < n; i++) h[i+1] = H[i], s[i+1] = s[i] + h[i+1];

	stack<ll> s;
	s.push(0);
	lpos[0][0] = 0;
	for(int i = 1; i <= n; i++) {
		while(h[s.top()] <= h[i]) s.pop();
		lpos[i][0] = s.top();
		lsum[i][0] = (h[s.top()] - h[i]) * (s.top() + 1);
		s.push(i);
	}
	for(int i = 1; i < L; i++) {
		for(int j = 0; j <= n+1; j++) {
			lpos[j][i] = lpos[lpos[j][i-1]][i-1];
			lsum[j][i] = lsum[j][i-1] + lsum[lpos[j][i-1]][i-1];
		}
	}
	s = stack<ll>();
	s.push(n+1);
	rpos[n+1][0] = n+1;
	for(int i = n; i >= 1; i--) {
		while(h[s.top()] <= h[i]) s.pop();
		rpos[i][0] = s.top();
		rsum[i][0] = (h[s.top()] - h[i]) * s.top();
		s.push(i);
	}
	for(int i = 1; i < L; i++) {
		for(int j = 0; j <= n+1; j++) {
			rpos[j][i] = rpos[rpos[j][i-1]][i-1];
			rsum[j][i] = rsum[j][i-1] + rsum[rpos[j][i-1]][i-1];
		}
	}
	return;
}

long long query(int S, int E){
	int p = E;
	int q = S;
	ll res = (E + 1) * h[E] - S * h[S];
	for(int i = L-1; i >= 0; i--) {
		if(lpos[p][i] >= S) {
			res += lsum[p][i];
			p = lpos[p][i];
		}
	}
	for(int i = L-1; i >= 0; i--) {
		if(rpos[q][i] <= E) {
			res -= rsum[q][i];
			q = rpos[q][i];
		}
	}
	res -= s[E] - s[S-1];
	return res;
}
