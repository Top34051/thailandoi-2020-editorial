#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;

int n,m,k;
int sz[maxn];
vector<pair<int,int>> p[maxn];
int has[maxn], pos[maxn];

int main() {
	scanf("%d%d%d",&m,&n,&k);
	for(int x=1;x<=n;x++) {

		// get probs
		scanf("%d",&sz[x]);
		for(int i=0;i<sz[x];i++) {
			int num,val; scanf("%d%d",&num,&val);
			p[x].push_back({num, val});
		}

		// calculate suffix probs
		for(int i=sz[x]-2;i>=0;i--) {
			p[x][i].second += p[x][i+1].second;
		}

		// initilize counters
		has[x] = 0; pos[x] = 0;
		while(pos[x] < sz[x] && p[x][pos[x]].first <= has[x]) pos[x]++;
	}


	// insert into heap
	priority_queue<pair<int,int>> pq;
	for(int x=1;x<=n;x++) {
		if(pos[x] < sz[x]) pq.push({p[x][pos[x]].second, x});
	}

	// solve
	long long ans = 0;
	while(m-- && !pq.empty()) {
		auto tmp = pq.top(); pq.pop();
		int val = tmp.first, x = tmp.second;

		// increment counters
		has[x]++;
		while(pos[x] < sz[x] && p[x][pos[x]].first <= has[x]) pos[x]++;

		// insert into heap
		if(pos[x] < sz[x]) pq.push({p[x][pos[x]].second, x});

		ans += val;
	}

	printf("%lf", (double)ans / k);
}