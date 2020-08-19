#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
const int inf = 2e9;

int n, m;
int speed[maxn];
vector<tuple<int,int,int,int>> holes, slows;
set<int> has[6];
int change[maxn][6], dist[maxn][6], stop[maxn];
pair<int,int> seg[6][maxn*4];

void build(int i, int pos, int l, int r) {
	if(l == r) {
		seg[i][pos] = {dist[l][i] - i * change[l][i], l};
		return ;
	}
	int mid = (l+r)/2;
	build(i,pos<<1,l,mid); build(i,pos<<1|1,mid+1,r);
	seg[i][pos] = min(seg[i][pos<<1], seg[i][pos<<1|1]);
}

void update(int i, int pos, int l, int r, int x, int val) {
	if(x < l || r < x) return ;
	if(l == r) {
		seg[i][pos] = {val, x};
		return ;
	}
	int mid = (l+r)/2;
	update(i,pos<<1,l,mid,x,val); update(i,pos<<1|1,mid+1,r,x,val);
	seg[i][pos] = min(seg[i][pos<<1], seg[i][pos<<1|1]);
}

pair<int,int> query(int i, int pos, int l, int r, int x, int y) {
	if(y < l || r < x) return {inf, 0};
	if(x <= l && r <= y) return seg[i][pos];
	int mid = (l+r)/2;
	return min(query(i,pos<<1,l,mid,x,y), query(i,pos<<1|1,mid+1,r,x,y));
}

int main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&speed[i]);
	for(int i=1;i<=m;i++) {
		int type; scanf("%d",&type);
		if(type == 1) {
			int ti,l,r,pos; scanf("%d%d%d%d",&ti,&l,&r,&pos); l++; r++;
			holes.push_back({ti,l,r,pos});
		}
		else {
			int ti,l,r,lim; scanf("%d%d%d%d",&ti,&l,&r,&lim); l++; r++;
			slows.push_back({ti,l,r,lim});
		}
	}

	sort(slows.begin(), slows.end(), [](tuple<int,int,int,int> x, tuple<int,int,int,int> y) { // sort slows by time
		return get<0>(x) < get<0>(y);
	});
	sort(holes.begin(), holes.end(), [](tuple<int,int,int,int> x, tuple<int,int,int,int> y) { // sort holes by position
		return get<3>(x) < get<3>(y);
	});

	// get change time
	for(int x=1;x<=n;x++) {
		for(int i=0;i<=5;i++) change[x][i] = i < speed[x] ? (int)1e8 + 1 : 1;
		for(int i=1;i<=5;i++) has[i].insert(x);
	}
	for(auto slow : slows) {
		auto [ti, l, r, lim] = slow;
		for(int i = lim; i <= 5; i++) {
			while(has[i].lower_bound(l) != has[i].end()) {
				int x = *has[i].lower_bound(l);
				if(x > r) break;
				change[x][i] = min(change[x][i], ti); // first time the speed changes to `i`
				has[i].erase(x);
			}
		}
	}
	for(int x=1;x<=n;x++) {
		dist[x][5] = 0;
		for(int i=4;i>=0;i--) dist[x][i] = dist[x][i+1] + (change[x][i] - change[x][i+1]) * (i+1);
		stop[x] = dist[x][0];
	}

	// assign holes
	for(int i=1;i<=5;i++) build(i,1,1,n);
	for(auto hole : holes) {
		auto [ti, l, r, pos] = hole;
		for(int i=1;i<=5;i++) { // iterate speeds
			while(true) {
				auto [val, x] = query(i,1,1,n,l,r);
				if(val > pos - ti * i) break; // dist[x][i] - i * change[x][i] <= pos - ti * i
				update(i,1,1,n,x,inf);
				stop[x] = min(stop[x], pos); // first hole it falls into
			}
		}
	}
	
	for(int x=1;x<=n;x++) printf("%d\n",stop[x]);
}