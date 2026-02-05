#ifdef LSC_ENV
#include "grader.cpp"
#endif

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MAXH = 202020;

struct Line {
	ll x1, y1, x2, y2;
	ll a;
};

struct Node {
	ll L, R, mx;
};

ll W, H, lazyl[4*MAXH], lazyr[4*MAXH];
Node tree[4*MAXH];

Node merge(Node l, Node r)
{
	Node res;
	res.L = max(l.L, r.L);
	res.R = max(l.R, r.R);
	res.mx = max({l.mx, r.mx, l.L + r.R});
	return res;
}

void push(int s, int e, int idx)
{
	tree[idx].L += lazyl[idx];
	tree[idx].R += lazyr[idx];
	tree[idx].mx += lazyl[idx] + lazyr[idx];
	if(s != e) {
		lazyl[2*idx] += lazyl[idx];
		lazyr[2*idx] += lazyr[idx];
		lazyl[2*idx+1] += lazyl[idx];
		lazyr[2*idx+1] += lazyr[idx];
	}
	lazyl[idx] = lazyr[idx] = 0;
}

void pull(int s, int e, int idx)
{
	tree[idx] = merge(tree[2*idx], tree[2*idx+1]);
}

void init(int s = 0, int e = H, int idx = 1)
{
	tree[idx] = {0, 0, 0};
	lazyl[idx] = lazyr[idx] = 0; 
	if(s == e) return;
	int m = (s + e) / 2;
	init(s, m, 2*idx);
	init(m+1, e, 2*idx+1);
}

void update(int l, int r, ll vl, ll vr, int s = 0, int e = H, int idx = 1)
{
	push(s, e, idx);
	if(e < l || r < s) return;
	if(l <= s && e <= r) {
		lazyl[idx] += vl;
		lazyr[idx] += vr;
		push(s, e, idx);
		return;
	}
	int m = (s + e) / 2;
	update(l, r, vl, vr, s, m, 2*idx);
	update(l, r, vl, vr, m+1, e, 2*idx+1);
	pull(s, e, idx);
}

ll solve(const vector<Line>& xs, const vector<Line>& ys)
{
	vector<vector<Line>> sx(W+1), ex(W+1);
	vector<vector<Line>> bar(W+1);
	for(const auto& l : xs) {
		sx[l.x1].push_back(l);
		ex[l.x2].push_back(l);
	}
	for(const auto& l : ys) {
		bar[l.x1].push_back(l);
	}

	init();
	for(int x = W; x >= 0; x--) {
		// push Ry
		for(const auto& l : bar[x]) update(l.y1, l.y2, 0, l.a);
		// push Rx
		for(const auto& l : sx[x]) update(l.y1, l.y2, 0, l.a);
	}

	ll C = 0;
	ll ans = -1e18;
	for(int x = 0; x <= W; x++) {
		for(const auto& l : sx[x]) {
			C += l.a;						// push Xx
			update(l.y1, l.y2, 0, -l.a);	// pop Rx
			update(0, l.y1-1, 0, -l.a);		// push Ux
			update(l.y2+1, H, -l.a, 0);		// push Dx
		}
		
		for(const auto& l : bar[x]) {
			C += l.a;						// push Xy
			update(l.y1, l.y2, 0, -l.a);	// pop Ry
			update(0, l.y1-1, 0, -l.a);		// push Uy
			update(l.y2+1, H, -l.a, 0);		// push Dy
		}

		ans = max(ans, tree[1].mx + C);
		
		for(const auto& l : bar[x]) {
			C -= l.a;						// pop Xy
			update(l.y1, l.y2, l.a, 0);		// push Ly
			update(0, l.y1-1, 0, l.a);		// pop Uy
			update(l.y2+1, H, l.a, 0);		// pop Dy
		}
		
		for(const auto& l : ex[x]) {
			C -= l.a;						// pop Xx
			update(l.y1, l.y2, l.a, 0);		// push Lx
			update(0, l.y1-1, 0, l.a);		// pop Ux
			update(l.y2+1, H, l.a, 0);		// pop Dx
		}
	}

	return ans;
}

ll get_max_score(int _W, int _H, vector<int> A, vector<int> X1, vector<int> Y1, vector<int> X2, vector<int> Y2)
{
	W = 2*_W;
	H = 2*_H;
	int N = A.size();
	vector<Line> xs, ys, rxs, rys;
	xs.reserve(N); ys.reserve(N);
	rxs.reserve(N); rys.reserve(N);
	for(int i = 0; i < N; i++) {
		X1[i] = 2*X1[i]; X2[i] = 2*X2[i];
		Y1[i] = 2*Y1[i]; Y2[i] = 2*Y2[i];
		if(X1[i] > X2[i]) swap(X1[i], X2[i]);
		if(Y1[i] > Y2[i]) swap(Y1[i], Y2[i]);
		if(X1[i] == X2[i]) {
			ys.push_back({X1[i], Y1[i], X2[i], Y2[i], A[i]});
			rys.push_back({W-X2[i], Y1[i], W-X1[i], Y2[i], A[i]});
		}
		else if(Y1[i] == Y2[i]) {
			xs.push_back({X1[i], Y1[i], X2[i], Y2[i], A[i]});
			rxs.push_back({W-X2[i], Y1[i], W-X1[i], Y2[i], A[i]});
		}
	}

	ll ans = max(solve(xs, ys), solve(rxs, rys));
	
	return ans;
}
