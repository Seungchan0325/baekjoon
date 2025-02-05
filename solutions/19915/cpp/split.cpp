#include <bits/stdc++.h>

#include "split.h"
// #include "grader.cpp"

using namespace std;

const int MAXN = 101010;

bool vst[MAXN];
int N, order[3], target[3], sz[MAXN], col[MAXN];
vector<int> ans, g[MAXN], t[MAXN];

void construct_tree(int u)
{
	vst[u] = true;
	for(auto v : g[u]) {
		if(vst[v]) continue;
		t[u].push_back(v);
		t[v].push_back(u);
		construct_tree(v);
	}
}

void get_sz(int u, int p)
{
	sz[u] = 1;
	for(auto v : t[u]) {
		if(v == p) continue;
		get_sz(v, u);
		sz[u] += sz[v];
	}
}

int get_cent(int u, int p)
{
	for(auto v : t[u]) {
		if(v == p) continue;
		if(sz[v] > N/2) return get_cent(v, u);
	}
	return u;
}

void coloring(int u, int color)
{
	vst[u] = true;
	col[u] = color;
	for(auto v : g[u]) {
		if(vst[v]) continue;
		coloring(v, color);
	}
}

void numbering(int u, int p, int num, int alt, int& cnt)
{
	if(cnt > 0) ans[u] = num, cnt--;
	else ans[u] = alt;
	for(auto v : t[u]) {
		if(v == p) continue;
		numbering(v, u, num, alt, cnt);
	}
}

vector<int> find_split(int n, int a, int b, int c, vector<int> p, vector<int> q) {
	N = n;
	order[0] = 1;
	order[1] = 2;
	order[2] = 3;
	target[0] = a;
	target[1] = b;
	target[2] = c;
	if(target[0] > target[1]) swap(target[0], target[1]), swap(order[0], order[1]);
	if(target[1] > target[2]) swap(target[1], target[2]), swap(order[1], order[2]);
	if(target[0] > target[1]) swap(target[0], target[1]), swap(order[0], order[1]);

	int m = p.size();
	for(int i = 0; i < m; i++) {
		g[p[i]].push_back(q[i]);
		g[q[i]].push_back(p[i]);
	}
	construct_tree(0);

	get_sz(0, -1);
	int cent = get_cent(0, -1);
	get_sz(cent, -1);

	vector<tuple<int, int, int>> arr;
	memset(vst, 0, sizeof(vst));
	vst[cent] = true;
	for(auto v : t[cent]) {
		if(!vst[v]) coloring(v, v);
		arr.emplace_back(col[v], sz[v], v);
	}
	sort(arr.begin(), arr.end(), greater<>());

	ans.resize(N);

	bool has_ans = false;
	int size = 0;
	int color = 0;
	vector<int> g1;
	for(auto [c, s, v] : arr) {
		if(c != color) {
			size = 0;
			color = c;
			g1.clear();
		}
		size += s;
		g1.push_back(v);
		if(size >= target[0]) {
			for(auto u : g1) {
				numbering(u, cent, order[0], order[2], target[0]);
			}
			has_ans = true;
			break;
		}
	}

	if(!has_ans) return ans;

	int cnt = target[1] - 1;
	ans[cent] = order[1];
	for(auto v : t[cent]) {
		if(ans[v]) continue;
		numbering(v, cent, order[1], order[2], cnt);
	}

	return ans;
}
