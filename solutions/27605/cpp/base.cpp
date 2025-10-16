#ifdef LSC_ENV
#include "grader.cpp"
#endif

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MAXN = 250505;
const ll mod = 1e9 + 7;

ll N, comb[MAXN], all, ans;
vector<pair<ll, ll>> g[MAXN];
set<pair<ll, ll>> s[MAXN];

ll nc2(ll n)
{
	return (long long)n * (n+1) / 2 % mod;
}

bool intersect(ll a, ll b, ll x, ll y)
{
	if(a > x) swap(a, x), swap(b, y);
	return b >= x-1;
}

pair<ll, ll> empty_space(set<pair<ll, ll>>& s, ll x)
{
	if(x < 0) return {0, -1};
	if(x >= N) return {N, N-1};
	auto it = s.lower_bound({x, -1});
	ll l, r;
	if(it == s.begin()) l = 0;
	else l = prev(it)->second+1;
	if(it == s.end()) r = N-1;
	else r = it->first-1;
	return {l, r};
}

void dfs(ll u, ll p)
{
	for(auto [v, w] : g[u]) {
		if(v == p) continue;
		dfs(v, u);
		ans = (ans + (long long)w * ((all - comb[v] + mod) % mod) % mod) % mod;

		if(s[u].size() < s[v].size()) {
			swap(s[u], s[v]);
			swap(comb[u], comb[v]);
		}

		for(auto [l, r] : s[v]) {
			auto it = s[u].lower_bound({l, r});
			while(it != s[u].begin() && intersect(l, r, prev(it)->first, prev(it)->second)) {
				auto [a, b] = *prev(it);
				l = min(l, a);
				r = max(r, b);

				auto [al, ar] = empty_space(s[u], a-1);
				comb[u] = ((comb[u] - nc2(ar-al+1)) % mod + mod) % mod;
				auto [bl, br] = empty_space(s[u], b+1);
				comb[u] = ((comb[u] - nc2(br-bl+1)) % mod + mod) % mod;
				comb[u] = ((comb[u] + nc2(br-al+1)) % mod + mod) % mod;

				comb[u] = ((comb[u] - nc2(b-a+1)) % mod + mod) % mod;
				s[u].erase(prev(it));
				it = s[u].lower_bound({l, r});
			}
			it = s[u].lower_bound({l, r});
			while(it != s[u].end() && intersect(l, r, it->first, it->second)) {
				auto [a, b] = *it;
				l = min(l, a);
				r = max(r, b);

				auto [al, ar] = empty_space(s[u], a-1);
				comb[u] = ((comb[u] - nc2(ar-al+1)) % mod + mod) % mod;
				auto [bl, br] = empty_space(s[u], b+1);
				comb[u] = ((comb[u] - nc2(br-bl+1)) % mod + mod) % mod;
				comb[u] = ((comb[u] + nc2(br-al+1)) % mod + mod) % mod;

				comb[u] = ((comb[u] - nc2(b-a+1)) % mod + mod) % mod;
				s[u].erase(it);
				it = s[u].lower_bound({l, r});
			}
			auto [al, ar] = empty_space(s[u], l-1);
			comb[u] = ((comb[u] - nc2(ar-al+1)) % mod + mod) % mod;
			s[u].emplace(l, r);
			comb[u] = ((comb[u] + nc2(r-l+1)) % mod + mod) % mod;
			auto [el, er] = empty_space(s[u], l-1);
			comb[u] = ((comb[u] + nc2(er-el+1)) % mod + mod) % mod;
			tie(el, er) = empty_space(s[u], r+1);
			comb[u] = ((comb[u] + nc2(er-el+1)) % mod + mod) % mod;
		}
	}

	ll l, r; l = r = u;
	auto it = s[u].lower_bound({l, r});
	while(it != s[u].begin() && intersect(l, r, prev(it)->first, prev(it)->second)) {
		auto [a, b] = *prev(it);
		l = min(l, a);
		r = max(r, b);

		auto [al, ar] = empty_space(s[u], a-1);
		comb[u] = ((comb[u] - nc2(ar-al+1)) % mod + mod) % mod;
		auto [bl, br] = empty_space(s[u], b+1);
		comb[u] = ((comb[u] - nc2(br-bl+1)) % mod + mod) % mod;
		comb[u] = ((comb[u] + nc2(br-al+1)) % mod + mod) % mod;

		comb[u] = ((comb[u] - nc2(b-a+1)) % mod + mod) % mod;
		s[u].erase(prev(it));
		it = s[u].lower_bound({l, r});
	}
	it = s[u].lower_bound({l, r});
	while(it != s[u].end() && intersect(l, r, it->first, it->second)) {
		auto [a, b] = *it;
		l = min(l, a);
		r = max(r, b);

		auto [al, ar] = empty_space(s[u], a-1);
		comb[u] = ((comb[u] - nc2(ar-al+1)) % mod + mod) % mod;
		auto [bl, br] = empty_space(s[u], b+1);
		comb[u] = ((comb[u] - nc2(br-bl+1)) % mod + mod) % mod;
		comb[u] = ((comb[u] + nc2(br-al+1)) % mod + mod) % mod;

		comb[u] = ((comb[u] - nc2(b-a+1)) % mod + mod) % mod;
		s[u].erase(it);
		it = s[u].lower_bound({l, r});
	}
	auto [al, ar] = empty_space(s[u], l-1);
	comb[u] = ((comb[u] - nc2(ar-al+1)) % mod + mod) % mod;
	s[u].emplace(l, r);
	comb[u] = ((comb[u] + nc2(r-l+1)) % mod + mod) % mod;
	auto [el, er] = empty_space(s[u], l-1);
	comb[u] = ((comb[u] + nc2(er-el+1)) % mod + mod) % mod;
	tie(el, er) = empty_space(s[u], r+1);
	comb[u] = ((comb[u] + nc2(er-el+1)) % mod + mod) % mod;
}

int maintenance_costs_sum(std::vector<int> U, std::vector<int> V, std::vector<int> W) {
	N = U.size() + 1;
	for(int i = 0; i+1 < N; i++) g[U[i]].emplace_back(V[i], W[i]), g[V[i]].emplace_back(U[i], W[i]);
	for(int i = 0; i < N; i++) {
		comb[i] = nc2(N);
	}

	all = nc2(N);
	dfs(0, -1);
	return ans;
}
