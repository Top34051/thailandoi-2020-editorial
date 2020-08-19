#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
const long long inf = 1e18;

int n, m;
int B[maxn];
long long circ, pos[maxn];
vector<int> coins[maxn];
long long st[maxn], ft[maxn];

long long walk(int x, int y) {
	if(y >= x) return pos[y] - pos[x];
	return circ + pos[y] - pos[x];
}

long long solve() {
	for(int x = 1; x <= n; x++) {
		m = max(m, B[x]);
		coins[B[x]].push_back(x);
		st[x] = ft[x] = inf;
	}

	for(int i = 1; i <= m; i++) {
    	// solve for st[x]
		for(auto x : coins[i]) {
			for(auto y : coins[i-1]) st[x] = min(st[x], ft[y] + min(walk(y, x), walk(x, y)));
			if(i == 1) st[x] = 0;
		}

	    // solve for ft[x]
		int sz = coins[i].size();
		if(sz == 1) ft[coins[i][0]] = st[coins[i][0]];
		else {
			for(int j = 0; j < sz; j++) {
				int x = coins[i][j], y;

				y = coins[i][(j+1)%sz];
				ft[x] = min(ft[x], st[y] + walk(y, x));

				y = coins[i][(j-1+sz)%sz];
				ft[x] = min(ft[x], st[y] + walk(x, y));
			}
		}
	}

  	// get answer
	long long ans = inf;
	for(auto x : coins[m]) ans = min(ans, ft[x]); 
	return ans;
}

int main() {
	scanf("%d",&n);
	for(int i = 1; i <= n; i++) scanf("%d", &B[i]);
		
	for(int i = 1;i <= n; i++) {
		int val; scanf("%d", &val);
		circ += val;
		if(i+1 <= n) pos[i+1] = pos[i] + val;
	}

	printf("%lld",solve());
}