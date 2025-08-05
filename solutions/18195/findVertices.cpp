#ifdef LSC_ENV
#include "grader.cpp"
#endif

#include "findVertices.h"

using namespace std;

bool query(vector<int> U, vector<int> V)
{
	if(U.empty() || V.empty()) return false;
	vector<int> u, v;
	for(int i = 1; i < U.size(); i++) {
		u.push_back(U[i-1]);
		v.push_back(U[i]);
	}
	for(int i = 1; i < V.size(); i++) {
		u.push_back(V[i-1]);
		v.push_back(V[i]);
	}
	return query(u, v, U[0], V[0]);
}

void find(int N)
{
	int sum = 0;
	for(int i = 0; i < 7; i++) {
		vector<int> U, V;
		for(int j = 1; j <= N; j++) {
			if(j&(1<<i)) U.push_back(j);
			else V.push_back(j);
		}
		if(query(U, V)) sum ^= (1<<i);
	}

	for(int i = 0; i < 7; i++) {
		if(sum&(1<<i)) {
			vector<int> U, V;
			for(int j = 1; j <= N; j++) {
				if(j&(1<<i)) U.push_back(j);
				else V.push_back(j);
			}
			int lo = -1;
			int hi = (int)U.size()-1;
			while(lo + 1 < hi) {
				int mid = (lo + hi) / 2;
				vector<int> sub(U.begin(), U.begin() + mid+1);
				if(query(sub, V)) hi = mid;
				else lo = mid;
			}
			int a = U[hi];
			answer(a, a^sum);
			break;
		}
	}
}
