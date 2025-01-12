#include <vector>
#include <bits/stdc++.h>

using namespace std;

struct Seg {
	int n;
	vector<int> tree, lazy;
	void init(int _n) {
		n = _n;
		tree.resize(4*n);
		lazy.resize(4*n);
	}

	void push(int s, int e, int idx)
	{
		if(lazy[idx]) {
			tree[idx] = max(tree[idx], lazy[idx]);
			if(s != e) {
				lazy[2*idx] = max(lazy[2*idx], lazy[idx]);
				lazy[2*idx+1] = max(lazy[2*idx+1], lazy[idx]);
			}
			lazy[idx] = 0;
		}
	}

	void update(int l, int r, int v, int s, int e, int idx)
	{
		push(s, e, idx);
		if(r < s || e < l) return;
		if(l <= s && e <= r) {
			lazy[idx] = v;
			push(s, e, idx);
			return;
		}

		int m = (s + e) / 2;
		update(l, r, v, s, m, 2*idx);
		update(l, r, v, m+1, e, 2*idx+1);
		tree[idx] = min(tree[2*idx], tree[2*idx+1]);
	}

	int query(int l, int r, int s, int e, int idx)
	{
		push(s, e, idx);
		if(r < s || e < l) return 1e9;
		if(l <= s && e <= r) return tree[idx];
		int m = (s + e) / 2;
		return min(query(l, r, s, m, 2*idx), query(l, r, m+1, e, 2*idx+1));
	}

	void update(int l, int r, int v)
	{
		update(l, r, v, 0, n-1, 1);
	}

	int query(int l, int r)
	{
		return query(l, r, 0, n-1, 1);
	}
} seg[16];

std::vector<int> find_sequence(int N, std::vector<int> L, std::vector<int> R, std::vector<int> X) {
	int m = L.size();
	for(int i = 0; i < 16; i++) seg[i].init(N);
	for(int i = 0; i < m; i++) {
		int g[16] = {};
		int t = X[i];
		for(int j : {2, 3, 5, 7, 11, 13}) {
			while(t%j==0) {
				g[j]++;
				t /= j;
			}
		}
		for(int j : {2, 3, 5, 7, 11, 13}) {
			if(seg[j].query(L[i], R[i]) > g[j]) {
				return vector<int>(N);
			}
			seg[j].update(L[i], R[i], g[j]);
		}
	}
	for(int i = 0; i < m; i++) {
		int g[16] = {};
		int t = X[i];
		for(int j : {2, 3, 5, 7, 11, 13}) {
			while(t%j==0) {
				g[j]++;
				t /= j;
			}
		}
		for(int j : {2, 3, 5, 7, 11, 13}) {
			if(seg[j].query(L[i], R[i]) != g[j]) {
				return vector<int>(N);
			}
		}
	}
	vector<int> ans(N, 1);
	for(int i = 0; i < N; i++) {
		for(int j : {2, 3, 5, 7, 9, 11, 13}) {
			ans[i] *= pow(j, seg[j].query(i, i));
		}
	}
	return ans;
}

int main() {
	int N, M;
	scanf("%d %d", &N, &M);

	std::vector<int> L, R, X;
	for (int i = 0; i < M; i++) {
		int l, r, x;
		scanf("%d %d %d", &l, &r, &x);
        l--; r--;
		L.push_back(l);
		R.push_back(r);
		X.push_back(x);
	}

	std::vector<int> result = find_sequence(N, L, R, X);
    if(result[0] == 0) printf("Impossible");
	else for (int i = 0; i < result.size(); i++) printf("%d ", result[i]);
}